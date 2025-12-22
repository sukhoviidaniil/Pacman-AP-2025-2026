/***************************************************************
 * Project:       Pacman
 * File:          CoinSpawn.h
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
#ifndef PACMAN_AST_COINSPAWN_H
#define PACMAN_AST_COINSPAWN_H
#include "Entity_Node.h"

namespace infra::ast {
    struct CoinSpawn : Entity_Node {
        int price = 100;
    };
}

#endif //PACMAN_AST_COINSPAWN_H