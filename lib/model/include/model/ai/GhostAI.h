/***************************************************************
 * Project:       Pacman
 * File:          GhostAI.h
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
#ifndef PACMAN_GHOSTAI_H
#define PACMAN_GHOSTAI_H
#include "internal/GhostFSM.h"
#include "internal/MovePolicy.h"
#include "mode_strategy/ChaseModeStrategy.h"
#include "mode_strategy/FrightenedModeStrategy.h"
#include "mode_strategy/ScatterModeStrategy.h"
#include "target_strategy/TargetStrategy.h"

namespace model::ai {
    // --- High-level GhostAI: brings everything together ---
    class GhostAI {
    public:
        GhostAI(
        std::unique_ptr<TargetStrategy> chase_target,
        std::unique_ptr<TargetStrategy> scatter_target,

        std::unique_ptr<MovePolicy> move_policy,
        std::unique_ptr<MovePolicy> frightened_policy

        )
        : chase_target_(std::move(chase_target))
        , scatter_target_(std::move(scatter_target))
        , move_policy_(std::move(move_policy))
        , frightened_policy_(std::move(frightened_policy))
        {
            // create modes
            chase_mode_ = std::make_unique<ChaseModeStrategy>(*chase_target_, *move_policy_);
            scatter_mode_ = std::make_unique<ScatterModeStrategy>(*scatter_target_, *move_policy_);
            frightened_mode_ = std::make_unique<FrightenedModeStrategy>(*frightened_policy_);

            fsm_.chase = chase_mode_.get();
            fsm_.scatter = scatter_mode_.get();
            fsm_.frightened = frightened_mode_.get();
        }

        infra::math::Direction decide(const GhostContext& ctx) const {
            return fsm_.select(ctx)->decide(ctx);
        }

    private:
        GhostFSM fsm_;

        std::unique_ptr<TargetStrategy> chase_target_;
        std::unique_ptr<TargetStrategy> scatter_target_;
        std::unique_ptr<MovePolicy> move_policy_;
        std::unique_ptr<MovePolicy> frightened_policy_;
        std::unique_ptr<ModeStrategy> chase_mode_;
        std::unique_ptr<ModeStrategy> scatter_mode_;
        std::unique_ptr<ModeStrategy> frightened_mode_;
    };
}

#endif //PACMAN_GHOSTAI_H