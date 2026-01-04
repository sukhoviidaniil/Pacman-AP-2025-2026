/***************************************************************
 * Project:       Pacman
 * File:          Game.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-02
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
#ifndef PACMAN_AST_APPLICATION_H
#define PACMAN_AST_APPLICATION_H


#include "infra/ast/event/Event_Collector.h"
#include "infra/ast/Node.h"
#include "infra/ast/view/View.h"
#include "infra/ast/Score.h"

namespace infra::ast {
    /**
     * @brief Represents the full game AST node.
     *
     * Inherits from Game_Node and aggregates the view configuration,
     * event collection, models, and score-related data.
     */
    struct Game : Game_Node{
        infra::ast::View view; ///< View configuration for the game
        infra::ast::Event_Collector event_collector; ///< Event collector for the game
        std::vector<infra::ast::Model> models; ///< List of game models
        ScoreBord score_bord; ///< Scoreboard data
    };
}

#endif //PACMAN_AST_APPLICATION_H