/***************************************************************
 * Project:       Pacman
 * File:          View_Sprites.h
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
#ifndef PACMAN_VIEW_SPRITES_H
#define PACMAN_VIEW_SPRITES_H
#include <string>
#include <vector>

#include "Sprite.h"
#include "Sprits_Group.h"

namespace infra::ast {
    struct View_Sprites {
        std::string type;
        std::vector<std::string> textures;
        std::vector<Sprite> sprites;
        std::vector<Sprits_Group> sprite_groups;

    };
}

#endif //PACMAN_VIEW_SPRITES_H