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

    struct Model_Visitor;
    struct Game_Visitor;

    /**
     * @brief Base class for all AST nodes.
     */
    struct Node {
        virtual ~Node() = default;
    };

    /**
     * @brief Base class for nodes in the "model" AST.
     *
     * Supports the visitor pattern via accept().
     */
    struct Model_Node : Node {
        ~Model_Node() override = default;

        /**
         * @brief Accepts a Model_Visitor for this node.
         *
         * @param v Visitor to process the node.
         *
         * @note Implementation is currently empty.
         */
        virtual void accept(Model_Visitor &v) const {

        }
    };

    /**
     * @brief Base class for nodes in the "game" AST.
     *
     * Supports the visitor pattern via accept().
     */
    struct Game_Node : Node {
        ~Game_Node() override = default;

        /**
         * @brief Accepts a Game_Visitor for this node.
         *
         * @param v Visitor to process the node.
         *
         * @note Implementation is currently empty.
         */
        virtual void accept(Game_Visitor &v) const {

        }
    };
}

#endif //PACMAN_AST_NODE_H