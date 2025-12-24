/***************************************************************
 * Project:       Pacman
 * File:          Sprite_Direction.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-09
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
#ifndef PACMAN_EXPRESSION_INFO_H
#define PACMAN_EXPRESSION_INFO_H

#include "infra/ast/Node.h"
#include "infra/math/Direction.h"

namespace infra::ast {
    struct Sprite_Direction : Node {
        math::Direction direction;
        int recLeft = -1, recTop = -1;
    };
}

#endif //PACMAN_EXPRESSION_INFO_H