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

#include "model/ai/internal/MovePolicy.h"
#include "model/ai/mode_strategy/ModeStrategy.h"

namespace model::ai {

    struct FrightenedModeStrategy : ModeStrategy {
        const MovePolicy& frightened_mover; // usually RandomMovePolicy
        explicit FrightenedModeStrategy(const MovePolicy& m) : frightened_mover(m) {}

        infra::math::Direction decide(const GhostContext& ctx) const override {
            // return frightened_mover.choose_direction(ctx.map, ctx.self_tile, {0,0});
        }
    };
}

#endif //PACMAN_FRIGHTENEDMODESTRATEGY_H