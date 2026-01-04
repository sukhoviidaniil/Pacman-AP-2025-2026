/***************************************************************
 * Project:       Pacman
 * File:          EatenModeStrategy.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-02
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
#ifndef PACMAN_EATENMODESTRATEGY_H
#define PACMAN_EATENMODESTRATEGY_H

#include "ModeStrategy.h"

namespace model::ai {
    struct EatenModeStrategy final : ModeStrategy {
        TilePos home_;

        EatenModeStrategy(const TilePos& home, const IPathFinder& pf)
            : ModeStrategy(pf)
            , home_(home)
        {}

        [[nodiscard]] infra::math::Direction decide(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
        ) const override {

            // In Eaten mode, the ghost always strives for home
            // turning is allowed, but we still prohibit meaningless backtracking
            // if there are alternatives
            const auto d = path_finder_.next_dir(
                u_ctx.permission,
                g_ctx.map,
                u_ctx.self_pos,
                home_,
                std::nullopt,
                IPathFinder::Optimize::MinDistance
            );

            // if pathfinder couldn't find the path — go straight
            return d.value_or(u_ctx.self_direction);
        }
    };
}

#endif //PACMAN_EATENMODESTRATEGY_H