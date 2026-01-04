/***************************************************************
 * Project:       Pacman
 * File:          ViewNode.h
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
#ifndef PACMAN_AST_VIEWNODE_H
#define PACMAN_AST_VIEWNODE_H
#include <string>

#include "infra/ast/Node.h"

namespace infra::ast {
    struct SpriteVisitor;
    /**
     * @brief Base class for sprite-related AST nodes.
     *
     * Stores texture information and sprite dimensions,
     * and supports the visitor pattern via accept().
     */
    struct SpriteNode : Node {
        std::string using_texture; ///< Name or path of the texture used
        unsigned int sprits_width; ///< Width of the sprite sheet
        unsigned int sprits_height; ///< Height of the sprite sheet
        ~SpriteNode() override = default;

        /**
         * @brief Accepts a SpriteVisitor to process this node.
         *
         * @param v Visitor instance.
         *
         * @note Default implementation is empty.
         */
        virtual void accept(SpriteVisitor &v) const {
        }
    };
}

#endif //PACMAN_AST_VIEWNODE_H