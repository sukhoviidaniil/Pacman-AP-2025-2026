/***************************************************************
 * Project:       Pacman
 * File:          Sprits_Group.h
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
#ifndef PACMAN_SPRITE_GROUP_H
#define PACMAN_SPRITE_GROUP_H
#include <string>
#include <vector>

#include "Sprite_Status.h"
#include "infra/Status.h"
#include "infra/ast/Node.h"

namespace infra::ast {
    struct Complex_Sprite : View_Node {
        std::string using_texture;
        unsigned int sprits_width;
        unsigned int sprits_height;
        std::vector<std::string> groups_names;
        std::unordered_map<
            Status,
            Sprite_Status
        > sprites_;

        void accept(View_Visitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_SPRITE_GROUP_H