/***************************************************************
 * Project:       Pacman
 * File:          TargetStrategy.h
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
#ifndef PACMAN_TARGETSTRATEGY_H
#define PACMAN_TARGETSTRATEGY_H
#include "model/ai/GhostContext.h"

namespace model::ai {

    /**
     * @brief Interface for calculating a ghost's target tile.
     *
     * Used by ChaseModeStrategy and ScatterModeStrategy to decide where the ghost should move.
     */
    struct TargetStrategy {
        virtual ~TargetStrategy() = default;

        /**
         * @brief Calculate the target tile for a ghost.
         *
         * @param g_ctx Global context containing Pac-Man and map info
         * @param u_ctx Unique ghost context (position, direction, role, etc.)
         * @return TilePos Target tile for pathfinding
         */
        [[nodiscard]] virtual TilePos target(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const = 0;
    };
}

#endif //PACMAN_TARGETSTRATEGY_H