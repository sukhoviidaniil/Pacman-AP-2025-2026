/***************************************************************
 * Project:       Pacman
 * File:          GreedyPathFinder.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-01
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
#ifndef PACMAN_GREEDYPATHFINDER_H
#define PACMAN_GREEDYPATHFINDER_H
#include "IPathFinder.h"

namespace model::ai {

    /**
     * @brief A pathfinder implementation that chooses the next move greedily.
     *
     * This algorithm selects the immediate direction that appears to move closer
     * (or further, depending on Optimize) to the target without considering the full path.
     */
    class GreedyPathFinder final : public IPathFinder {
    public:
        ~GreedyPathFinder() override = default;

        /**
         * @brief Determines the next direction using a greedy approach.
         *
         * @param permission Movement permission level
         * @param tiles The tile grid to navigate
         * @param from Current tile position
         * @param to Target tile position
         * @param forbidden_dir Optional direction that should not be chosen
         * @param opt Optimization strategy
         * @return Optional direction to move next; empty if no valid move is found
         */
        [[nodiscard]] std::optional<infra::math::Direction> next_dir(
            const Permission& permission,
            const TileGrid& tiles,
            TilePos from,
            TilePos to,
            std::optional<infra::math::Direction> forbidden_dir,
            Optimize opt
        ) const override;
    };
}

#endif //PACMAN_GREEDYPATHFINDER_H