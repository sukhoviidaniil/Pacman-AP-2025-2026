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
    // Basic Visitor Interfaces
    // ----------------------------

    /**
     * @brief Base visitor interface.
     *
     * Provides a virtual destructor for proper polymorphic cleanup.
     */
    struct Visitor {
        virtual ~Visitor() = default;
    };

    /**
     * @brief Visitor interface for model AST nodes.
     *
     * Can be extended to perform operations on Model nodes.
     */
    struct Model_Visitor : Visitor {
        /**
         * @brief Visit a Model node.
         *
         * @param m Model node to visit
         *
         * @note Default implementation does nothing.
         */
        virtual void visit(const Model& m) {}
    };

    /**
     * @brief Visitor interface for game AST nodes.
     *
     * Can be extended to perform operations on Game or Node objects.
     */
    struct Game_Visitor : Visitor {
        /**
         * @brief Visit a Game node.
         *
         * @param g Game node to visit
         *
         * @note Default implementation does nothing.
         */
        virtual void visit(const Game& g) {}
        virtual void visit(const Node&) {}
    };
}

#endif //PACMAN_VISITOR_H