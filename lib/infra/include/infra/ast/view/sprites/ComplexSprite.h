/***************************************************************
 * Project:       Pacman
 * File:          SpritsGroup.h
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
#ifndef PACMAN_SPRITEGROUP_H
#define PACMAN_SPRITEGROUP_H

#include <string>
#include <vector>

#include "infra/Status.h"
#include "infra/ast/view/ViewNode.h"
#include "infra/ast/view/external/Sprite_Status.h"

namespace infra::ast {
    struct ComplexSprite : SpriteNode {
        std::vector<std::string> groups_names;
        std::unordered_map<
            Status,
            Sprite_Status
        > groups_;

        void accept(SpriteVisitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_SPRITEGROUP_H