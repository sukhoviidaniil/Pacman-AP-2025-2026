/***************************************************************
 * Project:       Pacman
 * File:          FrightenedModeStrategy.h
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
#ifndef PACMAN_FRIGHTENEDMODESTRATEGY_H
#define PACMAN_FRIGHTENEDMODESTRATEGY_H

#include "model/ai/mode_strategy/ModeStrategy.h"

namespace model::ai {

    /**
     * @brief Strategy for ghosts in Frightened mode.
     *
     * Chooses a direction away from Pacman using the path-finder,
     * trying to maximize distance while avoiding reversal.
     */
    struct FrightenedModeStrategy : ModeStrategy{
        explicit FrightenedModeStrategy(const IPathFinder& pf) : ModeStrategy(pf) {}

        [[nodiscard]] infra::math::Direction decide(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const override {

            // Use path-finder to move away from Pacman
            const auto d = path_finder_.next_dir(
                u_ctx.permission,
                g_ctx.map,
                u_ctx.self_pos,
                g_ctx.pacman_pos,
                opposite(u_ctx.self_direction),
                IPathFinder::Optimize::MaxDistance
                );

            // If no direction found, continue current direction
            if (!d.has_value()) {
                return u_ctx.self_direction;
            }
            return d.value();
        }
    };
}

#endif //PACMAN_FRIGHTENEDMODESTRATEGY_H