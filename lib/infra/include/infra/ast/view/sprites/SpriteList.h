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
    /**
     * @brief Represents a list of sprites with shared rectangle offsets.
     *
     * Inherits from SpriteNode and stores a collection of sprite names,
     * along with common rectangle offsets for left and top coordinates.
     */
    struct SpriteList : SpriteNode{
        std::vector<std::string> names; ///< Names of sprites in the list
        Sprite_Rec recLeft; ///< Rectangle offsets for left coordinate
        Sprite_Rec recTop; ///< Rectangle offsets for top coordinate
        SpriteList() = default; ///< Default constructor
    };
}

#endif //PACMAN_SPRITELIST_H