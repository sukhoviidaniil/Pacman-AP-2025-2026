/***************************************************************
 * Project:       Pacman
 * File:          ModeStrategy.h
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
#ifndef PACMAN_MODESTRATEGY_H
#define PACMAN_MODESTRATEGY_H


#include "model/ai/GhostContext.h"
#include "model/ai/path_finder/IPathFinder.h"

namespace model::ai {
    // --- ModeStrategy: combination of TargetStrategy + MovePolicy (universal mode) ---
    struct ModeStrategy {
        const IPathFinder& path_finder_;
        explicit ModeStrategy(const IPathFinder& pf) : path_finder_(pf) {};

        virtual infra::math::Direction decide(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const = 0;
        virtual ~ModeStrategy() = default;
    };

}
#endif //PACMAN_MODESTRATEGY_H