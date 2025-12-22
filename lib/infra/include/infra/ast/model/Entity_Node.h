/***************************************************************
 * Project:       Pacman
 * File:          Entity_Node.h
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
#ifndef PACMAN_ENTITY_NODE_H
#define PACMAN_ENTITY_NODE_H
#include "infra/ast/Node.h"

namespace infra::ast {
    struct Entity_Node : Model_Node {
        float size = 39;
    };
}

#endif //PACMAN_ENTITY_NODE_H