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

#include <cstddef>
#include <type_traits>

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
    constexpr Direction opposite(const Direction d) {
        switch (d) {
            case Direction::Up: return Direction::Down;
            case Direction::Down: return Direction::Up;
            case Direction::Right: return Direction::Left;
            case Direction::Left: return Direction::Right;
            default: return Direction::Unknown; break;
        }
    }

    constexpr Direction by_index(const size_t d) {
        switch (d) {
            case 0: return Direction::Up;
            case 1: return Direction::Right;
            case 2: return Direction::Down;
            case 3: return Direction::Left;
            default: return Direction::Unknown; break;
        }
    }

    struct DirectionHash {
        size_t operator()(Direction d) const noexcept {
            return static_cast<std::size_t>(
                static_cast<std::underlying_type_t<Direction>>(d)
            );
        }
    };
}

#endif //PACMAN_DIRECTION_H