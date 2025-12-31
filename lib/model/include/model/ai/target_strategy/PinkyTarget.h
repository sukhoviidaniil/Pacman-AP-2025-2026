/***************************************************************
 * Project:       Pacman
 * File:          PinkyTarget.h
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
#ifndef PACMAN_PINKYTARGET_H
#define PACMAN_PINKYTARGET_H

#include "TargetStrategy.h"

namespace model::ai {
    struct PinkyTarget : TargetStrategy {
        TilePos target(const GhostContext& ctx) const override {
            using infra::math::Direction;
            // goal: cell 4 steps ahead in the direction pacman_dir
            TilePos t = ctx.pacman_pos;
            switch (ctx.pacman_dir) {
                case Direction::Up: t.y -= 4; break;
                case Direction::Down: t.y += 4; break;
                case Direction::Left: t.x -= 4; break;
                case Direction::Right: t.x += 4; break;
                default: break;
            }
            return t;
        }
    };
}

#endif //PACMAN_PINKYTARGET_H