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

#include <cfloat>
#include <queue>
#include <set>

#include "infra/math/to_Vector2.h"

namespace model::ai {

    std::optional<infra::math::Direction>
    model::ai::AStarPathFinder::next_dir(
        const Permission& permission,
        const TileGrid& tiles,
        TilePos from,
        TilePos to,
        std::optional<infra::math::Direction> forbidden_dir,
        IPathFinder::Optimize
    ) const
    {
    const size_t ROW = tiles.rows();
    const size_t COL = tiles.columns();

    auto isValid = [&](int y, int x) {
        return y >= 0 && x >= 0 &&
               y < static_cast<int>(ROW) && x < static_cast<int>(COL);
    };

    auto heuristic = [&](int y, int x) -> float {
        // Manhattan distance — корректна для 4 направлений
        return static_cast<float>(
            std::abs(y - static_cast<int>(to.y)) +
            std::abs(x - static_cast<int>(to.x))
        );
    };

    struct Cell {
        int py = -1;
        int px = -1;
        float f = FLT_MAX;
        float g = FLT_MAX;
        float h = FLT_MAX;
    };

    std::vector<std::vector<Cell>> cells(ROW, std::vector<Cell>(COL));
    std::vector<std::vector<bool>> closed(ROW, std::vector<bool>(COL, false));

    using Node = std::pair<float, TilePos>; // f, position
    std::set<Node> open;

    cells[from.y][from.x] = {
        static_cast<int>(from.y), static_cast<int>(from.x),
        0.f, 0.f, 0.f
    };
    open.insert({0.f, from});

    while (!open.empty()) {
        auto [_, cur] = *open.begin();
        open.erase(open.begin());

        if (cur == to)
            break;

        closed[cur.y][cur.x] = true;

        for (size_t i = 0; i < 4; ++i) {
            infra::math::Direction dir = infra::math::by_index(i);
            infra::math::Vector2 v = infra::math::to_vec(dir);

            int ny = static_cast<int>(cur.y + v.y);
            int nx = static_cast<int>(cur.x + v.x);

            if (!isValid(ny, nx)) continue;
            if (closed[ny][nx]) continue;

            TilePos next(ny, nx);

            if (!walkable(tiles.get_tile(next), permission))
                continue;

            // forbidden_dir — only for the first step
            if (cur == from && forbidden_dir.has_value()) {
                if (infra::math::equal(dir, *forbidden_dir))
                    continue;
            }

            float gNew = cells[cur.y][cur.x].g + 1.f;
            float hNew = heuristic(ny, nx);
            float fNew = gNew + hNew;

            if (cells[ny][nx].f > fNew) {
                open.insert({fNew, next});
                cells[ny][nx] = {
                    (int)cur.y, (int)cur.x,
                    fNew, gNew, hNew
                };
            }
        }
    }

    // path not found
    if (cells[to.y][to.x].py == -1)
        return std::nullopt;

    // path recovery — searching for the FIRST step
    TilePos cur = to;
    TilePos prev = cur;

    while (!(cur == from)) {
        prev = cur;
        const Cell& c = cells[cur.y][cur.x];
        cur = TilePos(c.py, c.px);
    }

    int dy = static_cast<int>(prev.y) - static_cast<int>(from.y);
    int dx = static_cast<int>(prev.x) - static_cast<int>(from.x);

    // convert the offset back to Direction
    for (size_t i = 0; i < 4; ++i) {
        infra::math::Direction dir = infra::math::by_index(i);
        infra::math::Vector2 v = infra::math::to_vec(dir);

        if (v.y == dy && v.x == dx)
            return dir;
    }

    return std::nullopt;
    }
}
