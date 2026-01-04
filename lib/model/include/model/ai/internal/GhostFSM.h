/***************************************************************
 * Project:       Pacman
 * File:          GhostFSM.h
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
#ifndef PACMAN_GHOSTFSM_H
#define PACMAN_GHOSTFSM_H

#include "model/ai/mode_strategy/ModeStrategy.h"

namespace model::ai {

    /**
     * @brief A simple finite state machine (FSM) for ghosts that selects
     *        the appropriate mode strategy based on the ghost's current mode.
     */
    struct GhostFSM {
        ///< Strategy for Chase mode (not owned)
        const ModeStrategy* chase = nullptr;
        ///< Strategy for Scatter mode (not owned)
        const ModeStrategy* scatter = nullptr;
        ///< Strategy for Frightened mode (not owned)
        const ModeStrategy* frightened = nullptr;
        ///< Strategy for Dead mode (not owned)
        const ModeStrategy* dead = nullptr;

        /**
         * @brief Selects the current mode strategy based on the ghost's context.
         *
         * @param ctx The unique context of a ghost
         * @return Pointer to the selected ModeStrategy
         */
        [[nodiscard]] const ModeStrategy* select(const UniqGhostContext& ctx) const {
            switch (ctx.mode) {
                case GhostMode::Chase:return chase;
                case GhostMode::Scatter: return scatter;
                case GhostMode::Frightened: return frightened;
                case GhostMode::Dead: return dead;
            }
            return chase; // fallback

        }
    };
}

#endif //PACMAN_GHOSTFSM_H