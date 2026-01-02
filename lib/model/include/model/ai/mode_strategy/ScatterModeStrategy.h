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

        infra::math::Direction decide(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const override {

            // TilePos tar = target.target(ctx);
            // return mover.choose_direction(ctx.map, ctx.self_tile, tar);
        }
    };
}

#endif //PACMAN_SCATTERMODESTRATEGY_H