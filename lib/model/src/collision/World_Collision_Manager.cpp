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

#include "model/Entity.h"


namespace model::collision {
    void World_Collision_Manager::resolve_сollision(const std::shared_ptr<model::Entity> &entityA, const std::shared_ptr<model::Entity> &entityB) const{
        // TODO
    }

    World_Collision_Manager::World_Collision_Manager(
        const std::shared_ptr<Collision_Control> &control,
        const std::shared_ptr<Tile_Grid> &world
        ):
        control_(control), grid_(world)
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

    void World_Collision_Manager::calculate_collision() const {
        if (!grid_ || !control_) return;

        const size_t columns = grid_->get_columns();
        const size_t rows = grid_->get_rows();

        std::unordered_set<EntityPair, EntityPairHash> checked_pairs;
        checked_pairs.reserve(1024);

        for (size_t c = 0; c < columns; ++c) {
            for (size_t r = 0; r < rows; ++r) {
                const std::shared_ptr<const Tile> tile = grid_->get_tile(r, c);
                if (!tile) continue;

                const auto& entities = tile->get_entities();

                if (entities.empty()) {
                    continue;
                }

                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {

                        const int nr = static_cast<int>(r) + dr;
                        const int nc = static_cast<int>(c) + dc;

                        // Border check
                        if (nr < 0 || nc < 0 ||
                            nr >= static_cast<int>(rows) ||
                            nc >= static_cast<int>(columns))
                        {
                            continue;
                        }

                        std::shared_ptr<const Tile> neighbor = grid_->get_tile(static_cast<size_t>(nr), static_cast<size_t>(nc));
                        if (!neighbor) continue;

                        const auto& neighbor_entities = neighbor->get_entities();
                        if (neighbor_entities.empty()) continue;

                        for (const auto& e1 : entities) {
                            auto hb1 = e1->get_hitboxe();
                            if (!hb1) continue;

                            for (const auto& e2 : neighbor_entities) {
                                // To avoid double checks
                                if (e1.get() == e2.get()) continue;
                                auto hb2 = e2->get_hitboxe();
                                if (!hb2) continue;

                                EntityPair pair{e1, e2};

                                // Check for duplicates
                                if (checked_pairs.contains(pair)) continue;

                                // Add so as not to count again
                                checked_pairs.insert(pair);

                                if (control_->collision(hb1, hb2)) {
                                    resolve_сollision(e1, e2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    bool World_Collision_Manager::collision_world(const std::shared_ptr<const HitBoxe> &entity) const {
        const AABB aabb = entity->get_aabb();

        const std::optional<std::pair<size_t, size_t>> temp = grid_->get_nearest_tile_size_t(aabb.center);
        if (!temp) {
            return false;
        }
        std::pair<size_t, size_t> adjusted_tile = temp.value();
        size_t minTileX = adjusted_tile.first - 1;
        size_t maxTileX = adjusted_tile.first + 1;
        size_t minTileY = adjusted_tile.second - 1;
        size_t maxTileY = adjusted_tile.second + 1;

        for (size_t y = minTileY; y <= maxTileY; ++y){
            for (size_t x = minTileX; x <= maxTileX; ++x){
                const std::shared_ptr<const Tile> tile = grid_->get_tile(x, y);
                if (tile == nullptr) continue;
                if (tile->walkable()) {
                    continue; // walkable cell — skip
                }
                if (control_->collision(entity, grid_->get_tile_hitboxe(x, y))) {// TODO
                    return true;
                }
            }
        }
        return false;
    }

    void World_Collision_Manager::update_Entity_Tile(const std::shared_ptr<Entity> &entity) const {
        grid_->update_Entity_Tile(entity);
    }

    std::shared_ptr<const Tile_Grid> World_Collision_Manager::get_grid() const {
        return grid_;
    }
}
