/***************************************************************
 * Project:       Pacman
 * File:          Expression_Info.h
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



#include "../AST_Base.h"
#include "infra/math/Vector2.h"
#include <string>

namespace infra::ast {
    struct Sprite_Expression : Node {
        std::string name = "None";
        math::Vector2 direction;
        int recLeft = -1, recTop = -1;

        void accept(Visitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_EXPRESSION_INFO_H