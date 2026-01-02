/***************************************************************
 * Project:       Pacman
 * File:          IPathfinder.h
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
#include "TileGrid.h"
#include "TilePos.h"

namespace model {
    class IPathfinder {
    public:
        virtual ~IPathfinder() = default;
        virtual std::optional<TilePos> next_step(
            const TileGrid& tiles,
            TilePos from,
            TilePos to,
            std::optional<infra::math::Direction> forbidden_dir
        ) = 0;
    };
}

#endif //PACMAN_IPATHFINDER_H