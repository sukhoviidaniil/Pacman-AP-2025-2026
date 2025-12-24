/***************************************************************
 * Project:       Pacman
 * File:          RI_Sprite.h
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
#ifndef PACMAN_AST_RI_SPRITE_H
#define PACMAN_AST_RI_SPRITE_H
#include "RenderNode.h"

namespace view::ui {
    struct RI_Sprite : RenderNode {
        /**
         * @brief Name or ID of the sprite resource.
         */
        std::string sprite;

    };
}
#endif //PACMAN_AST_RI_SPRITE_H