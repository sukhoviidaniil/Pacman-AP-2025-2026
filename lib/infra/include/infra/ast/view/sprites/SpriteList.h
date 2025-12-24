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

#include <string>
#include <vector>

namespace infra::ast {
    enum struct Order {
        Vertically,
        Horizontally
    };
    struct SpriteList : SpriteNode{
        Order order = Order::Vertically;
        std::vector<std::string> names;
        Sprite_Rec recLeft;
        Sprite_Rec recTop;
    };
}

#endif //PACMAN_SPRITELIST_H