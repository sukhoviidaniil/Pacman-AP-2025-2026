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

namespace model::ai {
    std::optional<infra::math::Direction> GreedyPathFinder::next_dir(
        const Permission& permission,
        const TileGrid& tiles,
        const TilePos from,
        const TilePos to,
        const std::optional<infra::math::Direction> forbidden_dir
    )const {
        using infra::math::Direction;

        struct Candidate {
            Direction dir;
            TilePos  pos;
            size_t   h;   // heuristic
        };

        std::vector<Candidate> candidates;

        auto try_dir = [&](Direction d, int dy, int dx) {
            if (forbidden_dir.has_value() && infra::math::equal(forbidden_dir.value(), d))
                return;

            const int ny = int(from.y) + dy;
            const int nx = int(from.x) + dx;
            if (ny < 0 || nx < 0) return;
            if (ny >= int(tiles.rows()) || nx >= int(tiles.columns())) return;

            TilePos next{size_t(ny), size_t(nx)};
            if (walkable(tiles.get_tile(next), permission)){
                return;
            }

            size_t h =
                (next.y > to.y ? next.y - to.y : to.y - next.y) +
                (next.x > to.x ? next.x - to.x : to.x - next.x);

            candidates.push_back({d, next, h});
        };

        try_dir(Direction::Up,    -1,  0);
        try_dir(Direction::Right,  0,  1);
        try_dir(Direction::Down,   1,  0);
        try_dir(Direction::Left,   0, -1);

        if (candidates.empty())
            return std::nullopt;

        auto best = std::min_element(
            candidates.begin(), candidates.end(),
            [](const Candidate& a, const Candidate& b) {
                return a.h < b.h;
            }
        );

        return best->dir;
    }
}