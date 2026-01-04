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
        const std::optional<infra::math::Direction> forbidden_dir,
        Optimize opt
        ) const
    {
        using infra::math::Direction;

        struct Node {
            TilePos pos;
            Direction first_dir; // первое направление от старта
        };

        std::vector<std::vector<bool>> visited(tiles.rows(), std::vector<bool>(tiles.columns(), false));
        std::queue<Node> q;

        // Запускаем BFS с первой вершины
        q.push({from, Direction::None});
        visited[from.y][from.x] = true;

        // Возможные направления и их дельты
        constexpr std::pair<Direction, std::pair<int,int>> moves[] = {
            {Direction::Up, {-1,0}},
            {Direction::Right, {0,1}},
            {Direction::Down, {1,0}},
            {Direction::Left, {0,-1}}
        };

        while (!q.empty()) {
            Node cur = q.front(); q.pop();

            // Если достигли цели и ищем минимальное расстояние
            if (opt == IPathFinder::Optimize::MinDistance && cur.pos == to)
                return cur.first_dir;

            // Перебираем соседей
            for (auto [dir, delta] : moves) {
                if (forbidden_dir && infra::math::equal(*forbidden_dir, dir))
                    continue;

                int ny = static_cast<int>(cur.pos.y) + delta.first;
                int nx = static_cast<int>(cur.pos.x) + delta.second;

                if (ny < 0 || nx < 0 || ny >= static_cast<int>(tiles.rows()) || nx >= static_cast<int>(tiles.columns()))
                    continue;

                TilePos next{static_cast<size_t>(ny), static_cast<size_t>(nx)};
                if (visited[next.y][next.x]) continue;
                if (!walkable(tiles.get_tile(next), permission)) continue;

                visited[next.y][next.x] = true;

                Direction first = (cur.first_dir == Direction::None ? dir : cur.first_dir);

                // Для максимизации дистанции можно пушить всех соседей без раннего выхода
                q.push({next, first});

                if (opt == IPathFinder::Optimize::MaxDistance && next == to)
                    return first; // если цель всё-таки задана, можно сразу вернуть
            }
        }

        return std::nullopt; // путь не найден
    }
}
