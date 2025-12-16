/***************************************************************
 * Project:       Pacman
 * File:          AST_Node.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-14
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
#ifndef PACMAN_AST_NODE_H
#define PACMAN_AST_NODE_H

namespace infra::ast {

    // forward declarations

    struct Node;

    struct Visitor {
        virtual ~Visitor() = default;
        virtual void visit(const Node&) {}
    };


    struct Node {
        virtual ~Node() = default;
        virtual void accept(Visitor &v) const {

        }
    };
}

#endif //PACMAN_AST_NODE_H