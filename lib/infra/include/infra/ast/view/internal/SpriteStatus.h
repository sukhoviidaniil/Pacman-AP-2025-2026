/***************************************************************
 * Project:       Pacman
 * File:          SpriteStatus.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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
#ifndef PACMAN_AST_STATUS_INFO_H
#define PACMAN_AST_STATUS_INFO_H
#include <vector>

#include "infra/ast/Node.h"
#include "infra/ast/view/internal/Sprite_Direction.h"
#include "infra/ast/view/internal/Sprite_Rec.h"
#include "infra/ast/view/sprites/Animation.h"

namespace infra::ast {
    struct SpriteStatus : Node{
        std::vector<Sprite_Direction> sprite_directions;
        Animation animation;
        Sprite_Rec recLeft;
        Sprite_Rec recTop;
    };
}

#endif //PACMAN_AST_STATUS_INFO_H