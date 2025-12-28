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

#include "model/ai/internal/MovePolicy.h"

#include "model/ai/mode_strategy/ModeStrategy.h"
#include "model/ai/target_strategy/TargetStrategy.h"

namespace model::ai {
    struct ChaseModeStrategy : ModeStrategy {
        const TargetStrategy& target;
        const MovePolicy& mover;
        ChaseModeStrategy(const TargetStrategy& t, const MovePolicy& m) : target(t), mover(m) {}

        infra::math::Direction decide(const GhostContext& ctx) const override {
            infra::math::Vector2 tar = target.target(ctx);
            // return mover.choose_direction(ctx.map, ctx.self_tile, tar);
        }
    };
}

#endif //PACMAN_CHASEMODESTRATEGY_H