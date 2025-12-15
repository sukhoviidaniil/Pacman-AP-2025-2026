/***************************************************************
 * Project:       Pacman
 * File:          Stage_Node.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-14
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
#ifndef PACMAN_STAGE_NODE_H
#define PACMAN_STAGE_NODE_H

#include "infra/ast/AST_Base.h"

namespace infra::ast {
    struct Stage : Node {
        ~Stage() override = default;
    };
}

#endif //PACMAN_STAGE_NODE_H