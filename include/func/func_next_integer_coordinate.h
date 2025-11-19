/***************************************************************
 * Project:       Pacman
 * File:          func_next_integer_coordinate.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-17
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
#ifndef PACMAN_FUNC_NEXT_INTEGER_COORDINATE_H
#define PACMAN_FUNC_NEXT_INTEGER_COORDINATE_H
#include <cmath>

#include "math/Vector2.h"

inline Math::Vector2 next_integer_coordinate (const Math::Vector2 &position, const Math::Vector2 &direction) {
    const float x = position.x;
    const float y = position.y;
    const float dx = direction.x;
    const float dy = direction.y;

    // Next vertical line
    const float nextX = (dx > 0) ? std::floor(x) + 1 : std::ceil(x) - 1;
    const float tX = (dx == 0) ? INFINITY : (nextX - x) / dx;
    // Next horizontal line
    const float nextY = (dy > 0) ? std::floor(y) + 1 : std::ceil(y) - 1;
    const float tY = (dy == 0) ? INFINITY : (nextY - y) / dy;

    // Choose which border will be closer
    const float t = std::min(tX, tY);

    return { x + dx * t, y + dy * t };
}

#endif //PACMAN_FUNC_NEXT_INTEGER_COORDINATE_H
