/***************************************************************
 * Project:       Pacman
 * File:          ViewVisitor.h
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
#ifndef PACMAN_VIEWVISITOR_H
#define PACMAN_VIEWVISITOR_H

#include "infra/ast/Visitor.h"

namespace infra::ast {
    // forward declarations

    // View
    struct Sprite;
    struct ComplexSprite;

    // ----------------------------
    // Visitor interface for sprites
    // ----------------------------

    /**
     * @brief Visitor interface for sprite-related nodes.
     *
     * Inherits from Visitor and provides visit methods for
     * individual sprite types. Can be extended to perform
     * operations on Sprite and ComplexSprite nodes.
     */
    struct SpriteVisitor : Visitor {
        /**
         * @brief Visit a simple sprite node.
         *
         * @param s Sprite node to visit.
         *
         * @note Default implementation does nothing.
         */
        virtual void visit(const Sprite& s) {}

        /**
         * @brief Visit a complex sprite node.
         *
         * @param cs ComplexSprite node to visit.
         *
         * @note Default implementation does nothing.
         */
        virtual void visit(const ComplexSprite& cs) {}
    };
}

#endif //PACMAN_VIEWVISITOR_H