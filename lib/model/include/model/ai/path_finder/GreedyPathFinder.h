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
    class GreedyPathFinder final : public IPathFinder {
    public:
        ~GreedyPathFinder() override = default;

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