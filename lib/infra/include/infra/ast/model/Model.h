/***************************************************************
 * Project:       Pacman
 * File:          Model.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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
#ifndef PACMAN_AST_MODEL_H
#define PACMAN_AST_MODEL_H


#include "Grid.h"

namespace infra::ast {
    struct Model : Model_Node{
        Grid grid;
    };
}
#endif //PACMAN_AST_MODEL_H