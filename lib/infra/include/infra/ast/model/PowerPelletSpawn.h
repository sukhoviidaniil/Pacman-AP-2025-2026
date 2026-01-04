/***************************************************************
 * Project:       Pacman
 * File:          PowerPelletSpawn.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-22
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
#ifndef PACMAN_AST_POWERPELLETSPAWN_H
#define PACMAN_AST_POWERPELLETSPAWN_H
#include "Entity_Node.h"

namespace infra::ast {
    /**
     * @brief Represents a power pellet spawn point in the model AST.
     *
     * Inherits from Entity_Node and defines hitbox size, name,
     * and duration of the power-up effect.
     */
    struct PowerPelletSpawn : Entity_Node {
        float hitbox_size; ///< Size of the power pellet's collision hitbox
        std::string name = "PowerPelletSpawn"; ///< Default name identifier
        float buff_duration = 0.f; ///< Duration of the power-up effect
    };
}

#endif //PACMAN_AST_POWERPELLETSPAWN_H