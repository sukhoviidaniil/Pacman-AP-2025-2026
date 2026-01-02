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
    // --- FSM: the simplest machine that switches modes based on the global state ---
    struct GhostFSM {
        const ModeStrategy* chase = nullptr; /// NOT OWNER
        const ModeStrategy* scatter = nullptr; /// NOT OWNER
        const ModeStrategy* frightened = nullptr; /// NOT OWNER
        const ModeStrategy* dead = nullptr; /// NOT OWNER


        const ModeStrategy* select(const UniqGhostContext& ctx) const {
            switch (ctx.mode) {
                case GhostMode::Chase:return chase;
                case GhostMode::Scatter: return scatter;
                case GhostMode::Frightened: return frightened;
                case GhostMode::Dead: return dead;
            }
            return chase;

        }
    };
}

#endif //PACMAN_GHOSTFSM_H