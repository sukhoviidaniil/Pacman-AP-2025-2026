/***************************************************************
 * Project:       Pacman
 * File:          InkyTarget.h
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
#ifndef PACMAN_INKYTARGET_H
#define PACMAN_INKYTARGET_H
#include "TargetStrategy.h"


namespace model::ai {
    struct InkyTarget : TargetStrategy {
        std::size_t blinky_index;

        infra::math::Vector2 target(const GhostContext& ctx) const override {
            auto blinky = ctx.blinky_positions[blinky_index];
            infra::math::Point2 ahead = ctx.pacman_pos;
            /*
            Vec2 blinky = ctx.ghost_tiles[0];
            Vec2 ahead = ctx.pacman_tile;
            switch (ctx.pacman_dir) {
                case Direction::Up: ahead.y -= 2; break;
                case Direction::Down: ahead.y += 2; break;
                case Direction::Left: ahead.x -= 2; break;
                case Direction::Right: ahead.x += 2; break;
                default: break;
            }
            // целевая точка = A + (A - Blinky) == 2*A - Blinky
            Vec2 target{ ahead.x * 2 - blinky.x, ahead.y * 2 - blinky.y };
            return target;
            */
        }
    };
}

#endif //PACMAN_INKYTARGET_H