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

    enum class AIType : std::uint8_t {

    };

    struct GhostInfo : Entity_Node {
        float speed = 0.1f;
        float amount_per_level = 0;
        AIType type;
    };

    struct GhostSpawn : Model_Node {
        GhostInfo Blinky;
        GhostInfo Pinky;
        GhostInfo Inky;
        GhostInfo Clyde;
        GhostInfo Sludgy;
        GhostInfo Shady;
    };
}

#endif //PACMAN_AST_GHOSTSPAWN_H