/***************************************************************
 * Project:       Pacman
 * File:          Tile.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-28
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
#ifndef PACMAN_TILE_H
#define PACMAN_TILE_H

namespace model {
    enum class Tile {
        Wall,
        Free
    };
    inline bool walkable(const Tile tile) {
        switch (tile) {
            case Tile::Free:
                return true;
            default:
                return false;
        }
    }
}

#endif //PACMAN_TILE_H
