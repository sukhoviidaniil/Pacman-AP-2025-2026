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
    struct SpriteList;
    struct ComplexSprite;

    // ----------------------------
    // Interfaces by category
    // ----------------------------
    struct SpriteVisitor : Visitor {
        virtual void visit(const Sprite&) {}
        virtual void visit(const SpriteList&) {}
        virtual void visit(const ComplexSprite&) {}
    };
}

#endif //PACMAN_VIEWVISITOR_H