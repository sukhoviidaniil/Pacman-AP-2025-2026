/***************************************************************
 * Project:       Pacman
 * File:          RenderNode.h
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
#ifndef PACMAN_RENDERNODE_H
#define PACMAN_RENDERNODE_H
#include "infra/ast/view/ViewNode.h"
#include "infra/ast/view/ViewVisitor.h"
#include "infra/presentation/external/Camera.h"

namespace view::ui {

    struct RI_Label;
    struct RI_Rectangle;
    struct RI_Sprite;
    struct RI_ComplexSprite;

    struct RenderVisitor : infra::ast::Visitor {
        virtual void visit(const RI_Label&) {}
        virtual void visit(const RI_Rectangle&) {}
        virtual void visit(const RI_Sprite&) {}
        virtual void visit(const RI_ComplexSprite&) {}
    };

    struct RenderNode : infra::ast::Node {

        virtual void accept(RenderVisitor &v) const = 0;
    };
}


#endif //PACMAN_RENDERNODE_H