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

    /**
     * @brief Strategy for a ghost's mode: combines path-finding with a decision policy.
     *
     * Each mode (Chase, Scatter, Frightened, Dead) uses a ModeStrategy to determine
     * the next movement direction given the global game state and the ghost's unique context.
     */
    struct ModeStrategy {
        ///< Reference to a path-finder (not owned)
        const IPathFinder& path_finder_;
        explicit ModeStrategy(const IPathFinder& pf) : path_finder_(pf) {};

        /**
         * @brief Decide the next movement direction for this ghost.
         *
         * @param g_ctx Global game state relevant to ghosts
         * @param u_ctx Unique context of this ghost
         * @return The chosen direction to move
         */
        [[nodiscard]] virtual infra::math::Direction decide(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const = 0;
        virtual ~ModeStrategy() = default;
    };
}
#endif //PACMAN_MODESTRATEGY_H