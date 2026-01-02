/***************************************************************
 * Project:       Pacman
 * File:          AStarPathFinder.cpp
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

#include "model/ai/path_finder/AStarPathFinder.h"

#include <queue>

namespace model::ai {
    std::optional<infra::math::Direction> AStarPathFinder::next_dir(
        const Permission &permission,
        const TileGrid &tiles,
        const TilePos from,
        const TilePos to,
        const std::optional<infra::math::Direction> forbidden_dir
        ) const {
        using infra::math::Direction;

        struct Node {
            TilePos pos;
            size_t g;              // cost from start
            size_t f;              // g + h
            Direction first_dir;   // first move from start
        };

        auto heuristic = [&](const TilePos& a) {
            return
                (a.y > to.y ? a.y - to.y : to.y - a.y) +
                (a.x > to.x ? a.x - to.x : to.x - a.x);
        };

        struct Cmp {
            bool operator()(const Node& a, const Node& b) const {
                return a.f > b.f; // min-heap
            }
        };

        std::priority_queue<Node, std::vector<Node>, Cmp> open;
        std::vector<std::vector<bool>> closed(
            tiles.rows(), std::vector<bool>(tiles.columns(), false)
        );

        auto try_push = [&](const Node& cur,
                            Direction d, int dy, int dx)
        {
            if (forbidden_dir.has_value() && infra::math::equal(forbidden_dir.value(), d))
                return;

            const int ny = static_cast<int>(cur.pos.y) + dy;
            const int nx = static_cast<int>(cur.pos.x) + dx;
            if (ny < 0 || nx < 0) return;
            if (ny >= static_cast<int>(tiles.rows()) || nx >= static_cast<int>(tiles.columns())) return;

            const TilePos next{static_cast<size_t>(ny), static_cast<size_t>(nx)};
            if (closed[next.y][next.x]) return;
            if (!walkable(tiles.get_tile(next), permission)) return;

            size_t g = cur.g + 1;
            size_t h = heuristic(next);
            Direction first =
                (cur.g == 0 ? d : cur.first_dir);

            open.push({next, g, g + h, first});
        };

        // start node
        open.push({from, 0, heuristic(from), Direction::None});

        while (!open.empty()) {
            Node cur = open.top();
            open.pop();

            if (closed[cur.pos.y][cur.pos.x])
                continue;

            closed[cur.pos.y][cur.pos.x] = true;

            if (cur.pos == to)
                return cur.first_dir;

            try_push(cur, Direction::Up,    -1,  0);
            try_push(cur, Direction::Right,  0,  1);
            try_push(cur, Direction::Down,   1,  0);
            try_push(cur, Direction::Left,   0, -1);
        }

        return std::nullopt;
    }
}
