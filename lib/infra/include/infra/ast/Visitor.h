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

    // Model
    struct Model;

    // Gen
    struct Game;
    struct Node;

    // ----------------------------
    // Basic Visitor
    // ----------------------------
    struct Visitor {
        virtual ~Visitor() = default;
    };

    struct Model_Visitor : Visitor {
        virtual void visit(const Model&) {}
    };

    struct Game_Visitor : Visitor {
        virtual void visit(const Game&) {}
        virtual void visit(const Node&) {}
    };
}

#endif //PACMAN_VISITOR_H