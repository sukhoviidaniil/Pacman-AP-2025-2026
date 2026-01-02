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

    struct FrightenedModeStrategy : ModeStrategy{
        explicit FrightenedModeStrategy(const IPathFinder& pf) : ModeStrategy(pf) {}

        infra::math::Direction decide(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const override {

            const auto d = path_finder_.next_dir(
                u_ctx.permission,
                g_ctx.map,
                u_ctx.self_pos,
                g_ctx.house_pos,
                opposite(u_ctx.self_direction)
                );
            if (!d.has_value()) {
                return u_ctx.self_direction;
            }
            return d.value();
        }
    };
}

#endif //PACMAN_FRIGHTENEDMODESTRATEGY_H