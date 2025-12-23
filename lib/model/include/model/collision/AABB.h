/***************************************************************
 * Project:       Pacman
 * File:          AABB.h
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
#ifndef PACMAN_AABB_H
#define PACMAN_AABB_H
#include <limits>

#include "infra/math/Vector2.h"

namespace model::collision {
    class AABB {
        public:
        infra::math::Point2 center = {0,0};
        infra::math::Vector2 extend = {0,0};

        float min_X = std::numeric_limits<float>::max();
        float max_X = -std::numeric_limits<float>::max();
        float min_Y = std::numeric_limits<float>::max();
        float max_Y = -std::numeric_limits<float>::max();

        [[nodiscard]] int get_floor_min_x() const;
        [[nodiscard]] int get_floor_max_x() const;
        [[nodiscard]] int get_floor_min_y() const;
        [[nodiscard]] int get_floor_max_y() const;
    };
}

#endif //PACMAN_AABB_H