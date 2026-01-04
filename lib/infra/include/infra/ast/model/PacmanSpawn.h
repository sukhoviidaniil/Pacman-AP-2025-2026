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
    /**
     * @brief Represents Pacman's spawn point in the model AST.
     *
     * Inherits from Entity_Node and includes movement speed.
     */
    struct PacmanSpawn : Entity_Node {
        float speed = 1.0; ///< Movement speed of Pacman
    };
}

#endif //PACMAN_AST_PACMAN_H
