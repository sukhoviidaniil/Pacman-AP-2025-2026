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

#include "sprite/Sprite.h"
#include "sprite/Sprits_Group.h"

namespace infra::ast {
    struct View {
        std::string type = "None";
        unsigned int window_width = 0;
        unsigned int window_height = 0;
        std::vector<std::string> textures;
        std::vector<Sprite> sprites;
        std::vector<Sprits_Group> sprite_groups;
    };
}

#endif //PACMAN_AST_VIEW_H