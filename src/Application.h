/***************************************************************
 * Project:       Pacman
 * File:          Application.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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
#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include "infra/ast/Application.h"
#include "../lib/core/include/core/Stage_Manager.h"
#include "core/factory/Stage_Factory.h"
#include "model/Game_Model.h"
#include "view/View.h"

class Application{

public:
    infra::Event_Bus eventbus_; // GLOBAL
    explicit Application(infra::ast::Application a);
private:

    // std::shared_ptr<TODO> control;
    std::shared_ptr<view::View> view_;
    std::vector<infra::ast::Model> models_;

    control::Stage_Manager stage_manager;
    std::shared_ptr<core::Stage_Factory> stage_factory_;
    std::string conf_path;
};

#endif //PACMAN_APPLICATION_H