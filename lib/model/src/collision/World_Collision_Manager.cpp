/***************************************************************
 * Project:       Pacman
 * File:          World_Collision_Manager.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
 * Modified:      []
 *
 * Description:   []
 *
 * Contact:
 *   Email:       sukhovii.daniil@gmail.com
 *
 * Disclaimer:
 *   This file is part of Pacman.
 *   Unauthorized use, reproduction, or distribution is prohibited.
***************************************************************/

#include "model/collision/World_Collision_Manager.h"

#include <cmath>
#include <unordered_set>

#include "../../include/model/entity/Entity.h"
#include "infra/diagnostics/Logger.h"


namespace model::collision {
    /*
    void World_Collision_Manager::resolve_сollision(const std::shared_ptr<model::Entity> &entityA, const std::shared_ptr<model::Entity> &entityB) const{

    }
    */

    World_Collision_Manager::World_Collision_Manager() = default;

    World_Collision_Manager::World_Collision_Manager(
        std::unique_ptr<Collision_Control> control,
        const std::shared_ptr<Tile_Grid> &world
        ):
        control_(std::move(control)), grid_(world)
    {
    }

    struct EntityPair {
        const std::shared_ptr<Entity> a;
        const std::shared_ptr<Entity> b;

        bool operator==(const EntityPair& other) const noexcept {
            return (a == other.a && b == other.b) ||
                   (a == other.b && b == other.a);
        }
    };

    struct EntityPairHash {
        std::size_t operator()(const EntityPair& p) const {
            const std::size_t h1 = std::hash<const Entity*>{}(p.a.get());
            const std::size_t h2 = std::hash<const Entity*>{}(p.b.get());
            return h1 < h2 ? (h1 ^ (h2 << 1)) : (h2 ^ (h1 << 1));
        }
    };

    void outside_the_borders() {
        std::string warn = "Collision with the World - going beyond boundaries. ";
        LOG(warn);
    }

    bool World_Collision_Manager::collision_world(const HitBox& entity) const {
        const AABB aabb = entity.get_aabb();
        const auto temp = grid_->get_nearest_TilePos(aabb.center);
        if (!temp.has_value()) {
            return false;
        }
        const Tile_Grid::TilePos adjusted_tile = temp.value();
        const size_t minTileX = adjusted_tile.x - 1;
        const size_t maxTileX = adjusted_tile.x + 1;
        const size_t minTileY = adjusted_tile.y - 1;
        const size_t maxTileY = adjusted_tile.y + 1;

        for (size_t y = minTileY; y <= maxTileY; ++y){
            for (size_t x = minTileX; x <= maxTileX; ++x){
                auto pos = Tile_Grid::TilePos(y,x);
                std::optional<Tile> t = grid_->get_tile(pos);
                if (!t.has_value()) {
                    outside_the_borders();
                    continue;
                }
                if (walkable(t.value())) {
                    continue; // walkable cell — skip
                }
                std::unique_ptr<collision::HitBox> hitbox = grid_->get_hitbox(pos);
                if (hitbox == nullptr) {
                    outside_the_borders();
                    return true;
                }
                if (control_->collision(entity, *hitbox)) {
                    return true;
                }
            }
        }
        return false;
    }

    std::optional<infra::math::Vector2> World_Collision_Manager::collision_mtv_world(const HitBox& entity, const infra::math::Vector2& displacement) const {

        const AABB aabb = entity.get_aabb();
        const auto temp = grid_->get_nearest_TilePos(aabb.center);
        if (!temp.has_value()) return std::nullopt;

        const Tile_Grid::TilePos adjusted_tile = temp.value();
        const size_t minTileX = adjusted_tile.x - 1;
        const size_t maxTileX = adjusted_tile.x + 1;
        const size_t minTileY = adjusted_tile.y - 1;
        const size_t maxTileY = adjusted_tile.y + 1;

        std::optional<infra::math::Vector2> final_mtv;
        infra::math::Vector2 move_dir = displacement;
        if (move_dir.length() > 0.f) move_dir.normalize();

        for (size_t y = minTileY; y <= maxTileY; ++y){
            for (size_t x = minTileX; x <= maxTileX; ++x){
                auto pos = Tile_Grid::TilePos(y, x);
                auto t = grid_->get_tile(pos);
                if (!t.has_value() || walkable(t.value())) continue;

                auto hitbox = grid_->get_hitbox(pos);
                if (hitbox == nullptr) continue;

                auto mtv = control_->collision_mtv(entity, *hitbox);
                if (mtv.has_value()) {
                    const float proj = mtv->dot(move_dir);
                    if (!final_mtv.has_value() || std::abs(proj) < displacement.length()) {
                        final_mtv = mtv.value();
                    }
                }
            }
        }
        return final_mtv;
    }

    std::shared_ptr<Tile_Grid> World_Collision_Manager::get_grid() const {
        return grid_;
    }
}
