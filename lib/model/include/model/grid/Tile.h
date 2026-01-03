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

    enum class Permission {
        Low,
        High,
        Full
    };

    enum class Tile {
        Wall,
        GhostSpawn,
        Barrier,
        Free,
    };

    [[nodiscard]] inline bool walkable(const Tile t, const Permission p = Permission::Low){
        switch (p){
            case Permission::Low : {
                switch (t) {
                    case Tile::Free:
                        return true;
                    default:
                        return false;
                }
            }
            case Permission::High : {
                switch (t) {
                    case Tile::Free:
                    case Tile::GhostSpawn:
                    case Tile::Barrier:
                        return true;
                    default:
                        return false;
                }
            }
            case Permission::Full : {
                return true;
            }
            default:
                return false;
        }
    }
}

#endif //PACMAN_TILE_H
