/***************************************************************
 * Project:       Pacman
 * File:          Direction.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-22
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
#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H

namespace infra::math {
    enum class Direction {
        Any,
        Up,
        Right,
        Down,
        Left,
        None,
        Unknown
    };

    constexpr bool equal(const Direction first, const Direction second) {
        if (first == Direction::Any) return true;
        if (second == Direction::Any) return false;
        return first == second;
    }
}

#endif //PACMAN_DIRECTION_H