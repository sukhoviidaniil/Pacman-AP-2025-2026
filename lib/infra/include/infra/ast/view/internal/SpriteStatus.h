/***************************************************************
 * Project:       Pacman
 * File:          SpriteStatus.h
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
#ifndef PACMAN_AST_STATUS_INFO_H
#define PACMAN_AST_STATUS_INFO_H
#include <vector>

#include "infra/ast/Node.h"
#include "infra/ast/view/internal/Sprite_Direction.h"
#include "infra/ast/view/internal/Sprite_Rec.h"
#include "infra/ast/view/sprites/Animation.h"

namespace infra::ast {
    /**
     * @brief Represents the visual status of a sprite.
     *
     * Inherits from Node and aggregates directional frames,
     * animation data, and rectangle offsets for rendering.
     */
    struct SpriteStatus : Node{
        std::vector<Sprite_Direction> sprite_directions; ///< List of directional sprite frames
        Animation animation; ///< Animation data for the sprite
        Sprite_Rec recLeft; ///< Rectangle offsets for left coordinate
        Sprite_Rec recTop; ///< Rectangle offsets for top coordinate
    };
}

#endif //PACMAN_AST_STATUS_INFO_H