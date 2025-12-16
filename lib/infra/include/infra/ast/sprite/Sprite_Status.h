/***************************************************************
 * Project:       Pacman
 * File:          Status_Info.h
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
#ifndef PACMAN_STATUS_INFO_H
#define PACMAN_STATUS_INFO_H
#include <vector>

#include "infra/ast/AST_Base.h"
#include "Sprite_Expression.h"
#include "Sprite_Rec.h"

namespace infra::ast {
    struct Sprite_Status : Node{
        std::vector<Sprite_Expression> facial_expressions;
        unsigned int number_of_expressions_per_direction = 0;
        Sprite_Rec recLeft;
        Sprite_Rec recTop;

        void accept(Visitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_STATUS_INFO_H