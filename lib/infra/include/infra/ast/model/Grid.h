/***************************************************************
 * Project:       Pacman
 * File:          Grid.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-18
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
#ifndef PACMAN_GRID_H
#define PACMAN_GRID_H

#include "infra/ast/Node.h"
#include <vector>
#include <cstdint>

namespace infra::ast {

    enum class Tile : std::uint8_t {
        Empty,
        Wall,
        CoinSpawn,
        PowerPelletSpawn,
        PacmanSpawn,
        GhostSpawn,
        Barrier
    };

    struct Grid : Model_Node {
        size_t rows;
        size_t columns;
        float tile_size;
        std::vector<std::vector<Tile>> grid;
    };
}
#endif //PACMAN_GRID_H
