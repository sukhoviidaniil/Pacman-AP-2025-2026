/***************************************************************
 * Project:       Pacman
 * File:          BFSPathFinder.cpp
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

#include "model/ai/path_finder/BFSPathFinder.h"

#include <queue>

namespace model::ai {
    std::optional<infra::math::Direction> BFSPathFinder::next_dir(
        const Permission &permission,
        const TileGrid &tiles,
        const TilePos from,
        const TilePos to,
        const std::optional<infra::math::Direction> forbidden_dir) const
    {

        using infra::math::Direction;

        struct Node {
            TilePos pos;
            Direction first_dir;
        };

        std::queue<Node> q;
        std::vector<std::vector<bool>> visited(
            tiles.rows(), std::vector<bool>(tiles.columns(), false)
        );

        auto try_push = [&](const TilePos& cur, Direction first,
                            Direction d, int dy, int dx)
        {
            if (forbidden_dir && infra::math::equal(*forbidden_dir, d))
                return;

            const int ny = static_cast<int>(cur.y) + dy;
            const int nx = static_cast<int>(cur.x) + dx;
            if (ny < 0 || nx < 0) return;
            if (ny >= static_cast<int>(tiles.rows()) || nx >= static_cast<int>(tiles.columns())) return;

            const TilePos next{static_cast<size_t>(ny), static_cast<size_t>(nx)};
            if (visited[next.y][next.x]) return;
            if (!walkable(tiles.get_tile(next), permission)) return;

            visited[next.y][next.x] = true;
            q.push({next, first});
        };

        visited[from.y][from.x] = true;

        try_push(from, Direction::Up,    Direction::Up,    -1,  0);
        try_push(from, Direction::Right, Direction::Right,  0,  1);
        try_push(from, Direction::Down,  Direction::Down,   1,  0);
        try_push(from, Direction::Left,  Direction::Left,   0, -1);

        while (!q.empty()) {
            Node cur = q.front();
            q.pop();

            if (cur.pos == to)
                return cur.first_dir;

            try_push(cur.pos, cur.first_dir, Direction::Up,    -1,  0);
            try_push(cur.pos, cur.first_dir, Direction::Right,  0,  1);
            try_push(cur.pos, cur.first_dir, Direction::Down,   1,  0);
            try_push(cur.pos, cur.first_dir, Direction::Left,   0, -1);
        }

        return std::nullopt;
    }
}
