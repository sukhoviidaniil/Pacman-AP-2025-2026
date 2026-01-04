/***************************************************************
 * Project:       Pacman
 * File:          IPathFinder.h
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
#ifndef PACMAN_IPATHFINDER_H
#define PACMAN_IPATHFINDER_H

#include "model/grid/TileGrid.h"
#include "model/grid/TilePos.h"

namespace model::ai {

    /**
     * @brief Interface for pathfinding algorithms on a tile grid.
     *
     * Implementations should provide logic to determine the next movement direction
     * from a current tile to a target tile.
     */
    class IPathFinder {
    public:
        IPathFinder() = default;
        virtual ~IPathFinder() = default;

        /**
         * @brief Optimization strategy for pathfinding.
         */
        enum class Optimize {
            MinDistance,
            MaxDistance
        };

        /**
         * @brief Calculates the next direction from a starting tile to a target tile.
         *
         * @param permission Movement permission level
         * @param tiles The tile grid to navigate
         * @param from Starting tile position
         * @param to Target tile position
         * @param forbidden_dir Optional direction that should not be chosen
         * @param opt Optimization strategy
         * @return Optional direction to move next; empty if no valid move is found
         */
        [[nodiscard]] virtual std::optional<infra::math::Direction> next_dir(
            const Permission& permission,
            const TileGrid& tiles,
            TilePos from,
            TilePos to,
            std::optional<infra::math::Direction> forbidden_dir,
            Optimize opt
        ) const = 0;
    };
}

#endif //PACMAN_IPATHFINDER_H