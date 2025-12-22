/***************************************************************
 * Project:       Pacman
 * File:          Pacman.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-16
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
#ifndef PACMAN_AST_PACMAN_H
#define PACMAN_AST_PACMAN_H
#include "Entity_Node.h"


namespace infra::ast {
    struct PacmanSpawn : Entity_Node {
        float size = 39;
        float speed = 1.0;
    };
}

#endif //PACMAN_AST_PACMAN_H
