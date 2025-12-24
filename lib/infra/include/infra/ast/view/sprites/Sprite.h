/***************************************************************
 * Project:       Pacman
 * File:          Sprite.h
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
#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H


#include "external/Sprite_Rec.h"
#include "infra/ast/view/ViewNode.h"

namespace infra::ast {
    struct Sprite : SpriteNode{
        std::string name;
        Sprite_Rec recLeft;
        Sprite_Rec recTop;
        void accept(SpriteVisitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_SPRITE_H