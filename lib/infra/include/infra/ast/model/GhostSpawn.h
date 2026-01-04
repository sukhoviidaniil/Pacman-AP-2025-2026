/***************************************************************
 * Project:       Pacman
 * File:          GhostSpawn.h
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
#ifndef PACMAN_AST_GHOSTSPAWN_H
#define PACMAN_AST_GHOSTSPAWN_H
#include <cstdint>

#include "Entity_Node.h"

namespace infra::ast {

    /**
     * @brief Available pathfinding algorithms for ghost AI.
     */
    enum class PathFinderType {
        AStar,
        BFS,
        Greedy
    };

    /**
     * @brief Contains configuration data for a ghost entity.
     *
     * Inherits from Entity_Node and defines speed, spawn amount,
     * and pathfinding behavior.
     */
    struct GhostInfo : Entity_Node {
        float base_speed = 0.1f; ///< Normal movement speed
        float base_speed_inc = 0.05f;
        float frightened_speed = 0.1f; ///< Speed when in frightened mode
        float frightened_speed_inc = 0.05f;
        float eaten_speed = 0.1f; ///< Speed after being eaten
        int start_amount = 1; ///< Initial number of ghosts
        float amount_per_level = 0; ///< Additional ghosts per level
        PathFinderType path_finder = PathFinderType::BFS; ///< Pathfinding algorithm
    };

    /**
     * @brief Node representing ghost spawn points for all four ghosts.
     *
     * Contains separate GhostInfo for Blinky, Pinky, Inky, and Clyde.
     */
    struct GhostSpawn : Model_Node {
        GhostInfo Blinky; ///< Configuration for Blinky
        GhostInfo Pinky; ///< Configuration for Pinky
        GhostInfo Inky; ///< Configuration for Inky
        GhostInfo Clyde; ///< Configuration for Clyde
    };
}

#endif //PACMAN_AST_GHOSTSPAWN_H