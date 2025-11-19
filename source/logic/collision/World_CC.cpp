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
    World_CC::World_CC() = default;

    World_CC::World_CC(const std::vector<std::vector<int>> &vector) {

        if (vector.empty()) {
            throw std::logic_error(""); // TODO Add expt
        }
        height_ = vector.size();

        if (vector.front().empty()) {
            throw std::logic_error(""); // TODO Add expt
        }
        width_ = vector.front().size();

        for (std::vector<int> row : vector) {
            if (row.size() != width_) {
                throw std::logic_error(""); // TODO Add expt
            }
        }

        world_ = vector;
    }

    World_CC::World_CC(const size_t height, const size_t width):
    height_(height), width_(width){
    }

    World_CC::~World_CC() = default;

    bool World_CC::collision(const HitBoxe_Shape &entity) {

        // вычисляем AABB сущности
        const AABB aabb = entity.get_aabb();
        // Предполагаю что у HitBoxe_Shape есть метод get_aabb()
        // который возвращает {minX, minY, maxX, maxY}

        const int minTileX = std::max(0, static_cast<int>(std::floor(aabb.min_X)));
        const int minTileY = std::max(0, static_cast<int>(std::floor(aabb.min_Y)));
        const int maxTileX = std::min(static_cast<int>(width_)  - 1, static_cast<int>(std::floor(aabb.max_X)));
        const int maxTileY = std::min(static_cast<int>(height_) - 1, static_cast<int>(std::floor(aabb.max_Y)));


        for (size_t y = minTileY; y <= maxTileY; ++y)
        {
            for (size_t x = minTileX; x <= maxTileX; ++x)
            {
                if (world_[y][x] == 0)
                    continue; // пустая клетка — пропускаем

                const float tx = static_cast<float>(x);
                const float ty = static_cast<float>(y);

                HitBoxe_Shape tile = HitBoxe_Shape({tx, ty}, 1, 1);

                if (Separating_Axis_Theorem::collision(entity, tile))
                    return true;
            }
        }
        return false;
    }
}
