/***************************************************************
 * Project:       Pacman
 * File:          to_Vector2.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-23
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
#ifndef PACMAN_TO_VECTOR2_H
#define PACMAN_TO_VECTOR2_H

#include "infra/math/Vector2.h"
#include "infra/math/Direction.h"

namespace infra::math {
    /**
     * @brief Converts a directional enum to a corresponding 2D vector.
     *
     * @param d Direction to convert.
     * @return Vector2 representing the direction.
     *
     * Maps Up/Right/Down/Left to unit vectors along axes.
     */
    constexpr Vector2 to_vec(const Direction d) {
        switch (d) {
            case Direction::Up:     return {0,-1};
            case Direction::Right:  return {1,0};
            case Direction::Down:   return {0,1};
            case Direction::Left:   return {-1,0};
            default:                return {0,0};
        }
    }
}

#endif //PACMAN_TO_VECTOR2_H