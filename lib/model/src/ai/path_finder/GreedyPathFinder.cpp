/***************************************************************
 * Project:       Pacman
 * File:          GreedyPathFinder.cpp
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

#include "model/ai/path_finder/GreedyPathFinder.h"

#include <cfloat>

namespace model::ai {
    std::optional<infra::math::Direction> GreedyPathFinder::next_dir(
        const Permission& permission,
        const TileGrid& tiles,
        const TilePos from,
        const TilePos to,
        const std::optional<infra::math::Direction> forbidden_dir,
        Optimize opt
    )const {
        using infra::math::Direction;

        const size_t ROW = tiles.rows();
        const size_t COL = tiles.columns();

        auto isValid = [&](int y, int x) {
            return y >= 0 && x >= 0 && y < static_cast<int>(ROW) && x < static_cast<int>(COL);
        };

        auto heuristic = [&](int y, int x) -> float {
            // Manhattan distance, since movement is only possible in 4 directions
            return static_cast<float>(std::abs(y - static_cast<int>(to.y)) +
                                      std::abs(x - static_cast<int>(to.x)));
        };

        // Possible directions
        constexpr std::pair<Direction, std::pair<int,int>> moves[] = {
            {Direction::Up, {-1,0}},
            {Direction::Right, {0,1}},
            {Direction::Down, {1,0}},
            {Direction::Left, {0,-1}}
        };

        TilePos cur = from;
        Direction first_move = Direction::None;

        std::vector<std::vector<bool>> visited(ROW, std::vector<bool>(COL, false));
        visited[cur.y][cur.x] = true;

        while (!(cur == to)) {
            TilePos best_next = cur;
            float best_h = FLT_MAX;
            Direction best_dir = Direction::None;

            for (auto [dir, delta] : moves) {
                int ny = static_cast<int>(cur.y) + delta.first;
                int nx = static_cast<int>(cur.x) + delta.second;

                if (!isValid(ny, nx)) continue;
                TilePos next{static_cast<size_t>(ny), static_cast<size_t>(nx)};
                if (visited[next.y][next.x]) continue;
                if (!walkable(tiles.get_tile(next), permission)) continue;

                // forbidden_dir — only on the first step
                if (cur == from && forbidden_dir && infra::math::equal(dir, *forbidden_dir))
                    continue;

                float h = heuristic(ny, nx);
                if (h < best_h) {
                    best_h = h;
                    best_next = next;
                    best_dir = dir;
                }
            }

            if (best_dir == Direction::None) {
                // no valid moves
                return std::nullopt;
            }

            if (first_move == Direction::None)
                first_move = best_dir;

            cur = best_next;
            visited[cur.y][cur.x] = true;
        }

    return first_move;
    }
}
