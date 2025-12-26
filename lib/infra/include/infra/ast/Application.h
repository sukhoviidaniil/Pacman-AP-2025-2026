/***************************************************************
 * Project:       Pacman
 * File:          Application.h
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
    struct Application : Application_Node{
        infra::ast::View view;
        infra::ast::Event_Collector event_collector;
        std::vector<infra::ast::Model> models;
        ScoreSetup score_setup;
        ScoreBord score_bord;
    };
}

#endif //PACMAN_AST_APPLICATION_H