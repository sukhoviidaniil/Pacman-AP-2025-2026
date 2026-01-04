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

#include "mode_strategy/ChaseModeStrategy.h"
#include "mode_strategy/EatenModeStrategy.h"
#include "mode_strategy/FrightenedModeStrategy.h"
#include "mode_strategy/ScatterModeStrategy.h"
#include "target_strategy/CornerTargetStrategy.h"
#include "target_strategy/TargetStrategy.h"

namespace model::ai {

    /**
     * @brief High-level AI controller for a ghost.
     *
     * GhostAI acts as a facade that combines:
     * - finite state machine (FSM),
     * - movement/pathfinding policy,
     * - target selection strategies,
     * - behavior modes (chase, scatter, frightened, dead).
     *
     * It is responsible for selecting the current behavior mode
     * and delegating the decision-making to it.
     */
    class GhostAI {
    public:
        /**
         * @brief Constructs a GhostAI instance.
         *
         * Initializes all behavior modes and wires them into the FSM.
         *
         * @param home Tile position used as a reference point
         *             (e.g. respawn or return location).
         * @param chase_target Strategy used to compute chase targets.
         * @param scatter_target Strategy used to compute scatter targets.
         * @param move_policy Pathfinding / movement policy.
         */
        GhostAI(
        const TilePos& home,
        std::unique_ptr<TargetStrategy> chase_target,
        std::unique_ptr<TargetStrategy> scatter_target,

        std::unique_ptr<IPathFinder> move_policy

        )
        : chase_target_(std::move(chase_target))
        , scatter_target_(std::move(scatter_target))
        , move_policy_(std::move(move_policy))
        {
            // create modes
            chase_mode_ = std::make_unique<ChaseModeStrategy>(*chase_target_, *move_policy_);
            scatter_mode_ = std::make_unique<ScatterModeStrategy>(*scatter_target_, *move_policy_);
            frightened_mode_ = std::make_unique<FrightenedModeStrategy>(*move_policy_);
            dead_mode_ = std::make_unique<EatenModeStrategy>(home, *move_policy_);

            fsm_.chase = chase_mode_.get();
            fsm_.scatter = scatter_mode_.get();
            fsm_.frightened = frightened_mode_.get();
            fsm_.dead = dead_mode_.get();
        }

        /**
         * @brief Decides the next movement direction for the ghost.
         *
         * Selects the active mode via the FSM and delegates
         * the decision to the corresponding strategy.
         *
         * @param g_ctx Global context shared between ghosts.
         * @param u_ctx Context specific to this ghost.
         * @return Chosen movement direction.
         */
        [[nodiscard]] infra::math::Direction decide(const GlobalGhostContext& g_ctx, const UniqGhostContext& u_ctx) const {
            return fsm_.select(u_ctx)->decide(g_ctx, u_ctx);
        }

    private:
        /**
         * @brief Finite state machine controlling ghost modes.
         */
        GhostFSM fsm_;

        /**
         * @brief Target strategy used in chase mode.
         */
        std::unique_ptr<TargetStrategy> chase_target_;

        /**
         * @brief Target strategy used in scatter mode.
         */
        std::unique_ptr<TargetStrategy> scatter_target_;

        /**
         * @brief Target strategy used in dead/eaten mode.
         * @todo Clarify if this is planned to be used or can be removed.
         */
        std::unique_ptr<TargetStrategy> dead_target_;

        /**
         * @brief Movement/pathfinding policy shared across modes.
         */
        std::unique_ptr<IPathFinder> move_policy_;

        /**
         * @brief Strategy implementing chase behavior.
         */
        std::unique_ptr<ModeStrategy> chase_mode_;

        /**
         * @brief Strategy implementing scatter behavior.
         */
        std::unique_ptr<ModeStrategy> scatter_mode_;

        /**
         * @brief Strategy implementing frightened behavior.
         */
        std::unique_ptr<ModeStrategy> frightened_mode_;

        /**
         * @brief Strategy implementing dead/eaten behavior.
         */
        std::unique_ptr<ModeStrategy> dead_mode_;
    };
}

#endif //PACMAN_GHOSTAI_H