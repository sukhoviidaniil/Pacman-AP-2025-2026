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

#include "CoinSpawn.h"
#include "GhostSpawn.h"
#include "Grid.h"
#include "PacmanSpawn.h"
#include "PowerPelletSpawn.h"

namespace infra::ast {
    /**
     * @brief Represents the complete game model AST.
     *
     * Inherits from Model_Node and aggregates all main components:
     * grid layout, entity spawns for Pacman, ghosts, coins, and power pellets.
     */
    struct Model : Model_Node{
        Grid grid; ///< Game grid layout
        PacmanSpawn pacman_spawn; ///< Game grid layout
        GhostSpawn ghost_spawn; ///< Ghost starting positions
        CoinSpawn coin_spawn; ///< Coin spawn configuration
        PowerPelletSpawn power_pellet_spawn; ///< Power pellet spawn configuration
    };
}

#endif //PACMAN_AST_MODEL_H