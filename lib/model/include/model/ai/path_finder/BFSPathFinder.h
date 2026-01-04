/***************************************************************
 * Project:       Pacman
 * File:          BFSPathFinder.h
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
#ifndef PACMAN_BFSPATHFINDER_H
#define PACMAN_BFSPATHFINDER_H
#include "IPathFinder.h"

namespace model::ai {

    /**
     * @brief A pathfinder implementation using Breadth-First Search (BFS).
     *
     * This algorithm explores the tile grid level by level to find the shortest
     * path from the start tile to the target tile.
     */
    class BFSPathFinder : public IPathFinder {
    public:
        ~BFSPathFinder() override = default;

        /**
         * @brief Calculates the next direction using BFS pathfinding.
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
            Optimize opt
        ) const override;
    };
}

#endif //PACMAN_BFSPATHFINDER_H
