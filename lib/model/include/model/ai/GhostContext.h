/***************************************************************
 * Project:       Pacman
 * File:          GhostContext.h
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
#ifndef PACMAN_GHOSTCONTEXT_H
#define PACMAN_GHOSTCONTEXT_H
#include <span>

#include "internal/GhostMode_State.h"
#include "infra/math/Direction.h"

#include "model/grid/TileGrid.h"

namespace model::ai {
    struct GlobalGhostContext {
        const TileGrid& map;
        TilePos pacman_pos;
        TilePos house_pos;
        infra::math::Direction pacman_direction;
        std::span<const TilePos> blinky_positions;
    };
    struct UniqGhostContext {
        Permission permission;
        GhostMode mode;
        TilePos self_pos;
        infra::math::Direction self_direction;
        std::size_t self_index; // index among peers
    };
}

#endif //PACMAN_GHOSTCONTEXT_H