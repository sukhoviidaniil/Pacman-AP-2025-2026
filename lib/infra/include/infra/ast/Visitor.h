/***************************************************************
 * Project:       Pacman
 * File:          Visitor.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-17
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
#ifndef PACMAN_VISITOR_H
#define PACMAN_VISITOR_H

namespace infra::ast {
    // forward declarations

    // View
    struct Sprite;
    struct Sprite_Expression;
    struct Sprite_Rec;
    struct Sprite_Status;
    struct Complex_Sprite;
    struct Camera;
    struct View;
    struct Text;
    struct Rectangle;
    struct Scene_Entity;
    struct Scene_Model;
    struct Scene_UI;
    struct Scene_Graph;

    // Model
    struct Model;

    // Gen
    struct Application;
    struct Node;

    // ----------------------------
    // Basic Visitor
    // ----------------------------
    struct Visitor {
        virtual ~Visitor() = default;
    };

    // ----------------------------
    // Interfaces by category
    // ----------------------------
    struct View_Visitor : Visitor {
        virtual void visit(const Sprite&) {}
        virtual void visit(const Sprite_Expression&) {}
        virtual void visit(const Sprite_Rec&) {}
        virtual void visit(const Sprite_Status&) {}
        virtual void visit(const Complex_Sprite&) {}
        virtual void visit(const Camera&) {}
        virtual void visit(const View&) {}
        virtual void visit(const Text&) {}
        virtual void visit(const Rectangle&) {}
        virtual void visit(const Scene_Entity&) {}
        virtual void visit(const Scene_Model&) {}
        virtual void visit(const Scene_UI&) {}
        virtual void visit(const Scene_Graph&) {}
    };

    struct Model_Visitor : Visitor {
        virtual void visit(const Model&) {}
    };

    struct Application_Visitor : Visitor {
        virtual void visit(const Application&) {}
        virtual void visit(const Node&) {}
    };
}

#endif //PACMAN_VISITOR_H