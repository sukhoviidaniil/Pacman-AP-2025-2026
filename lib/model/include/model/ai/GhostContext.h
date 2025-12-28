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
#include "infra/math/Point2.h"
#include "../Grid/Tile_Grid.h"

namespace model::ai {
    struct  GhostContext {
        // Not unique info
        const Tile_Grid& map;
        infra::math::Point2 pacman_pos;
        infra::math::Direction pacman_dir;
        GhostMode global_mode;
        std::span<const infra::math::Point2> blinky_positions;

        // Unique info per ghost
        infra::math::Point2 self_pos;
        std::size_t self_index; // index among peers
    };
}

#endif //PACMAN_GHOSTCONTEXT_H