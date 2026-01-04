/***************************************************************
 * Project:       Pacman
 * File:          TilePos.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-31
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
#ifndef PACMAN_TILEPOS_H
#define PACMAN_TILEPOS_H

#include <cstddef>
#include <tuple>

namespace model {

    /**
     * @brief Represents a position in the tile grid.
     *
     * Uses row (y) and column (x) indexing.
     */
    struct TilePos {
        size_t y, x; /// y - row, x - colum

        /**
         * @brief Constructs a tile position.
         * @param y Row index
         * @param x Column index
         */
        TilePos(const size_t y, const size_t x) : y(y), x(x) {}

        /**
         * @brief Equality comparison.
         */
        bool operator==(const TilePos& other) const noexcept {
            return y == other.y && x == other.x;
        }

        /**
         * @brief Lexicographical comparison for ordering.
         */
        bool operator<(const TilePos& other) const {
            return std::tie(y, x) < std::tie(other.y, other.x);
        }
    };

    /**
     * @brief Checks if two tile positions are adjacent or the same.
     *
     * @param a First tile position
     * @param b Second tile position
     * @return True if positions are at most 1 tile apart in both directions
     */
    inline bool are_close(const TilePos& a, const TilePos& b) noexcept {
        const size_t dy = (a.y > b.y) ? (a.y - b.y) : (b.y - a.y);
        const size_t dx = (a.x > b.x) ? (a.x - b.x) : (b.x - a.x);
        return dy <= 1 && dx <= 1;
    }
}

#endif //PACMAN_TILEPOS_H