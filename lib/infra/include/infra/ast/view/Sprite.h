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
#include "infra/ast/Node.h"
#include "infra/ast/Visitor.h"

namespace infra::ast {
    struct Sprite : View_Node{
        void accept(View_Visitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_SPRITE_H