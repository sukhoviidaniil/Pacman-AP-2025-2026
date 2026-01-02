/***************************************************************
 * Project:       Pacman
 * File:          ChaseModeStrategy.h
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
#ifndef PACMAN_CHASEMODESTRATEGY_H
#define PACMAN_CHASEMODESTRATEGY_H



#include "model/ai/mode_strategy/ModeStrategy.h"
#include "model/ai/target_strategy/TargetStrategy.h"

namespace model::ai {
    struct ChaseModeStrategy : ModeStrategy {
        const TargetStrategy& target;
        ChaseModeStrategy(const TargetStrategy& t, const IPathFinder& pf) : ModeStrategy (pf), target(t) {}

        [[nodiscard]] infra::math::Direction decide(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const override {
            TilePos tar = target.target(g_ctx, u_ctx);

            const auto d = path_finder_.next_dir(
                u_ctx.permission,
                g_ctx.map,
                u_ctx.self_pos,
                tar,
                opposite(u_ctx.self_direction),
                IPathFinder::Optimize::MaxDistance
                );
            if (!d.has_value()) {
                return u_ctx.self_direction;
            }
            return d.value();
        }
    };
}

#endif //PACMAN_CHASEMODESTRATEGY_H