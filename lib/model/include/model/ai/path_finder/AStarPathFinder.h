/***************************************************************
 * Project:       Pacman
 * File:          AStarPathFinder.h
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
#ifndef PACMAN_ASTARPATHFINDER_H
#define PACMAN_ASTARPATHFINDER_H
#include "IPathFinder.h"

namespace model::ai {

    /**
     * @brief A pathfinder implementation using the A* algorithm.
     *
     * This algorithm finds an optimal path from the start tile to the target tile
     * using a heuristic to prioritize exploration of promising tiles.
     */
    class AStarPathFinder final : public IPathFinder {
    public:
        ~AStarPathFinder() override = default;

        /**
         * @brief Determines the next move using the A* search algorithm.
         *
         * @param permission Movement permission level
         * @param tiles The tile grid to navigate
         * @param from Starting tile position
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
            IPathFinder::Optimize opt
        ) const override;
    };
}

#endif //PACMAN_ASTARPATHFINDER_H