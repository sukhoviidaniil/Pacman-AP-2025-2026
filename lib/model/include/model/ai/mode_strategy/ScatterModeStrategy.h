/***************************************************************
 * Project:       Pacman
 * File:          ScatterModeStrategy.h
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
#ifndef PACMAN_SCATTERMODESTRATEGY_H
#define PACMAN_SCATTERMODESTRATEGY_H

#include "model/ai/mode_strategy/ModeStrategy.h"
#include "model/ai/target_strategy/TargetStrategy.h"

namespace model::ai {
    struct ScatterModeStrategy : ModeStrategy {
        const TargetStrategy& target;
        ScatterModeStrategy(const TargetStrategy& t, const IPathFinder& pf) : ModeStrategy (pf), target(t) {}

        [[nodiscard]] infra::math::Direction decide(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const override {

            // Scatter: target — fixed tile (card corner)
            TilePos tar = target.target(g_ctx, u_ctx);

            const auto d = path_finder_.next_dir(
                u_ctx.permission,
                g_ctx.map,
                u_ctx.self_pos,
                tar,
                opposite(u_ctx.self_direction), // no turning
                IPathFinder::Optimize::MinDistance
            );

            // if the path is not found, continue moving
            return d.value_or(u_ctx.self_direction);
        }
    };
}

#endif //PACMAN_SCATTERMODESTRATEGY_H