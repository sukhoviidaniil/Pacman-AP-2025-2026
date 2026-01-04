/***************************************************************
 * Project:       Pacman
 * File:          CornerTargetStrategy.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-02
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
#ifndef PACMAN_CORNERTARGETSTRATEGY_H
#define PACMAN_CORNERTARGETSTRATEGY_H
#include "TargetStrategy.h"

namespace model::ai {

    /**
     * @brief Always targets a fixed corner of the map.
     * Useful for Scatter mode.
     */
    struct CornerTargetStrategy final : TargetStrategy {
        TilePos corner_{0,0};

        explicit CornerTargetStrategy(const TileGrid& map, infra::math::Direction preferred_corner) {
            // Search for a tile corresponding to the “corner” of the map depending on preferred_corner
            size_t row = 0, col = 0;


            switch (preferred_corner) {
                case infra::math::Direction::Up:    row = 0; break;
                case infra::math::Direction::Down:  row = map.rows() - 1; break;
                case infra::math::Direction::Left:  col = 0; break;
                case infra::math::Direction::Right: col = map.columns() - 1; break;
                default: break;
            }

            // Find first passable tile in corner (searching from row/col outwards)
            for (size_t r = row; r < map.rows(); ++r) {
                for (size_t c = col; c < map.columns(); ++c) {
                    TilePos pos(r, c);
                    if (walkable(map.get_tile(pos), Permission::Low)) {
                        corner_ = pos;
                        return;
                    }
                }
            }

            // fallback — center of the map
            corner_ = TilePos(map.rows()/2, map.columns()/2);
        }

        [[nodiscard]] TilePos target(
            const GlobalGhostContext& /*g_ctx*/,
            const UniqGhostContext& /*u_ctx*/
        ) const override {
            return corner_;
        }
    };
}

#endif //PACMAN_CORNERTARGETSTRATEGY_H