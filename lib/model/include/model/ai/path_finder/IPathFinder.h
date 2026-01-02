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
    class IPathFinder {
    public:
        IPathFinder() = default;
        virtual ~IPathFinder() = default;

        enum class Optimize { MinDistance, MaxDistance };
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