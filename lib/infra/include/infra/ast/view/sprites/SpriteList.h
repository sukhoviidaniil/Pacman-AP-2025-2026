/***************************************************************
 * Project:       Pacman
 * File:          SpriteList.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-24
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
#ifndef PACMAN_SPRITELIST_H
#define PACMAN_SPRITELIST_H

#include <vector>

#include "json.hpp"
#include "infra/ast/view/ViewNode.h"
#include "infra/ast/view/internal/Sprite_Rec.h"

namespace infra::ast {
    struct SpriteList : SpriteNode{
        std::vector<std::string> names;
        Sprite_Rec recLeft;
        Sprite_Rec recTop;
        SpriteList() = default;
    };
}

#endif //PACMAN_SPRITELIST_H