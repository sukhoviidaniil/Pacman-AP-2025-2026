/***************************************************************
 * Project:       Pacman
 * File:          Sprite.h
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
#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H

#include "infra/ast/view/internal/Sprite_Rec.h"
#include "infra/ast/view/ViewNode.h"
#include "infra/ast/view/ViewVisitor.h"

namespace infra::ast {
    /**
     * @brief Represents a simple sprite node.
     *
     * Inherits from SpriteNode and defines a name and rectangle
     * offsets within a sprite sheet. Supports the visitor pattern.
     */
    struct Sprite : SpriteNode{
        std::string name; ///< Name of the sprite
        int recLeft; ///< Left coordinate in the sprite sheet
        int recTop; ///< Top coordinate in the sprite sheet

        /**
         * @brief Accepts a SpriteVisitor to process this sprite.
         *
         * @param v Visitor instance
         */
        void accept(SpriteVisitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_SPRITE_H