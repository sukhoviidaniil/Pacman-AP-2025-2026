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

    struct View_Visitor;
    struct Model_Visitor;
    struct Application_Visitor;

    struct Node {
        virtual ~Node() = default;
    };
    struct View_Node : Node {
        ~View_Node() override = default;
        virtual void accept(View_Visitor &v) const {
        }
    };
    struct Model_Node : Node {
        ~Model_Node() override = default;
        virtual void accept(Model_Visitor &v) const {

        }
    };
    struct Application_Node : Node {
        ~Application_Node() override = default;
        virtual void accept(Application_Visitor &v) const {

        }
    };
}

#endif //PACMAN_AST_NODE_H