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
#include <string>
#include <vector>

#include "infra/ast/Node.h"
namespace infra::ast {
    struct Grid : Model_Node {
        unsigned int rows;
        unsigned int columns;
        float tile_size;
        std::vector<std::vector<std::string>> grid;
    };
}
#endif //PACMAN_GRID_H
