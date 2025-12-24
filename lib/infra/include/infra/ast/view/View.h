/***************************************************************
 * Project:       Pacman
 * File:          View.h
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
#ifndef PACMAN_AST_VIEW_H
#define PACMAN_AST_VIEW_H


#include <string>
#include <vector>

#include "infra/ast/view/sprites/Sprite.h"
#include "infra/ast/view/sprites/ComplexSprite.h"
#include "infra/ast/view/sprites/SpriteList.h"

namespace infra::ast {
    struct View : Node{
        std::string type = "None";
        unsigned int window_width = 0;
        unsigned int window_height = 0;
        std::vector<std::string> textures;
        std::vector<Sprite> sprites;
        std::vector<SpriteList> sprite_lists;
        std::vector<ComplexSprite> complex_sprites;
    };
}

#endif //PACMAN_AST_VIEW_H