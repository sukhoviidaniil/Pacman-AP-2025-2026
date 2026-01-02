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
    struct PowerPelletSpawn : Entity_Node {
        float hitbox_size;
        std::string name = "PowerPelletSpawn";
        float buff_duration = 0.f;
    };
}

#endif //PACMAN_AST_POWERPELLETSPAWN_H