/***************************************************************
 * Project:       Pacman
 * File:          Animation.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-28
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
#ifndef PACMAN_AST_ANIMATION_H
#define PACMAN_AST_ANIMATION_H
#include "infra/ast/Node.h"

namespace infra::ast {
    struct Animation : Node {
        size_t size = 0;
        float frame_duration = 1.f;
        int recLeft_increase = 0;
        int recTop_increase = 0;
    };
}

#endif //PACMAN_AST_ANIMATION_H