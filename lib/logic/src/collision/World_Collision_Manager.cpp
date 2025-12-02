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

#include "logic/collision/World_Collision_Manager.h"

#include <cmath>
#include <unordered_set>

namespace Logic::Collision {
    void World_Collision_Manager::resolve_сollision(const std::shared_ptr<Model::Entity> &entityA, const std::shared_ptr<Model::Entity> &entityB) const{
        // TODO
    }

    World_Collision_Manager::World_Collision_Manager(const std::shared_ptr<Collision_Control> &control, const std::shared_ptr<Tile_Grid> &world):
    control_(control), grid_(world){
    }


    struct EntityPair {
        const Model::Entity* a;
        const Model::Entity* b;

        bool operator==(const EntityPair& other) const {
            return a == other.a && b == other.b;
        }
    };

    struct EntityPairHash {
        std::size_t operator()(const EntityPair& p) const {
            // Address combination — sufficient
            return std::hash<const void*>()(p.a) ^ (std::hash<const void*>()(p.b) << 1);
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
                std::shared_ptr<Tile> tile = grid_->get_tile(r, c);
                if (!tile) continue;

                const auto& entities = tile->get_entities();

                if (entities.empty()) {
                    continue;
                }

                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {

                        int nr = static_cast<int>(r) + dr;
                        int nc = static_cast<int>(c) + dc;

                        // Border check
                        if (nr < 0 || nc < 0 || nr >= static_cast<int>(rows) || nc >= static_cast<int>(columns)) {
                            continue;
                        }

                        std::shared_ptr<Tile> neighbor = grid_->get_tile(static_cast<size_t>(nr), static_cast<size_t>(nc));
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

                                // Sort the pair (minimum address first)
                                const Model::Entity* a = e1.get() < e2.get() ? e1.get() : e2.get();
                                const Model::Entity* b = e1.get() < e2.get() ? e2.get() : e1.get();

                                EntityPair pair{a, b};

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

    bool World_Collision_Manager::collision_world(const std::shared_ptr<HitBoxe> &entity) const {
        const AABB aabb = entity->get_aabb();
        const size_t minTileX = static_cast<size_t>(std::max(0, static_cast<int>(std::floor(aabb.min_X))));
        const size_t minTileY = static_cast<size_t>(std::max(0, static_cast<int>(std::floor(aabb.min_Y))));
        const size_t maxTileX = static_cast<size_t>(std::min(static_cast<int>(grid_->get_width())  - 1, static_cast<int>(std::floor(aabb.max_X))));
        const size_t maxTileY = static_cast<size_t>(std::min(static_cast<int>(grid_->get_height()) - 1, static_cast<int>(std::floor(aabb.max_Y))));

        for (size_t y = minTileY; y <= maxTileY; ++y){
            for (size_t x = minTileX; x <= maxTileX; ++x){
                const std::shared_ptr<Tile> tile = grid_->get_tile(x, y);
                if (tile->get_status() == 0) {
                    continue; // empty cell — skip
                }
                std::shared_ptr<HitBoxe> tile_hitbox = tile->get_hitbox();
                if (control_->collision(entity, tile_hitbox)) {
                    return true;
                }
            }
        }
        return false;
    }

    void World_Collision_Manager::update_Entity_Tile(const std::shared_ptr<Model::Entity> &entity) const {
        grid_->update_Entity_Tile(entity);
    }

    std::shared_ptr<Tile_Grid> World_Collision_Manager::get_grid() const {
        return grid_;
    }

    Math::Vector2 World_Collision_Manager::get_next_tile_center(const Math::Vector2 &pos, const Math::Vector2 &dir) const {
        return grid_->get_next_tile_center(pos, dir);
    }
}
