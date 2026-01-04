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
    /**
     * @brief Axis-Aligned Bounding Box (AABB) for collision detection.
     *
     * Stores the center point and half-extents (size in each axis)
     * of the rectangle aligned to the axes.
     */
    class AABB {
        public:
        infra::math::Point2 center = {0,0}; ///< Center position of the box
        infra::math::Vector2 extend = {0,0}; ///< Half-widths in x and y directions
    };
}

#endif //PACMAN_AABB_H