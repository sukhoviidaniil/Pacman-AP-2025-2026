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

    /**
     * @brief Inky's targeting strategy: vector-based targeting using Pac-Man's position and Blinky's position.
     *        Calculates a point "ahead" of Pac-Man, then reflects Blinky's position across it.
     */
    struct InkyTarget : TargetStrategy {
        std::size_t blinky_index;

        [[nodiscard]] TilePos target(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const override {
            using infra::math::Direction;
            const auto blinky = g_ctx.blinky_positions[blinky_index];
            TilePos ahead = g_ctx.pacman_pos;

            switch (g_ctx.pacman_direction) {
                case Direction::Up: ahead.y -= 2; break;
                case Direction::Down: ahead.y += 2; break;
                case Direction::Left: ahead.x -= 2; break;
                case Direction::Right: ahead.x += 2; break;
                default: break;
            }
            // target point = A + (A - Blinky) == 2*A - Blinky
            TilePos target{ ahead.y * 2 - blinky.y, ahead.x * 2 - blinky.x,};
            g_ctx.map.limit(target);
            return target;

        }
    };
}

#endif //PACMAN_INKYTARGET_H