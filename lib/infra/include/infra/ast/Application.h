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

#include "infra/ast/Node.h"
#include "model/Model.h"
#include "view/View.h"

namespace infra::ast {
    struct Application : Application_Node{
        View view;
        std::vector<Model> models;
    };
}

#endif //PACMAN_AST_APPLICATION_H