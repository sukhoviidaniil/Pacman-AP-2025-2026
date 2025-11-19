/***************************************************************
 * Project:       Pacman
 * File:          World_CC.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-18
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

#include "logic/collision/World_CC.h"

#include <cmath>
#include <stdexcept>

#include "logic/collision/AABB.h"

namespace Logic::Collision {

    World_CC::World_CC(const std::shared_ptr<Tile_Grid> &world):
    world_(world){
        height_ = world_->get_height();
        width_ = world_->get_width();
    }

    World_CC::~World_CC() = default;


    bool World_CC::collision(const std::shared_ptr<HitBoxe> &entity) {
        const AABB aabb = entity->get_aabb();
        const size_t minTileX = static_cast<size_t>(std::max(0, static_cast<int>(std::floor(aabb.min_X))));
        const size_t minTileY = static_cast<size_t>(std::max(0, static_cast<int>(std::floor(aabb.min_Y))));
        const size_t maxTileX = static_cast<size_t>(std::min(static_cast<int>(width_)  - 1, static_cast<int>(std::floor(aabb.max_X))));
        const size_t maxTileY = static_cast<size_t>(std::min(static_cast<int>(height_) - 1, static_cast<int>(std::floor(aabb.max_Y))));

        for (size_t y = minTileY; y <= maxTileY; ++y){
            for (size_t x = minTileX; x <= maxTileX; ++x){
                std::shared_ptr<Tile> tile = world_->get_tile(x, y);
                if (tile->get_status() == 0) {
                    continue; // empty cell — skip
                }
                std::shared_ptr<HitBoxe> tile_hitbox = tile->get_hitbox();
                if (Separating_Axis_Theorem::collision(entity, tile_hitbox))
                    return true; //
            }
        }
        return false;
    }
}
