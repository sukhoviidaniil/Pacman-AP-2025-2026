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

#include "Score.h"
#include "infra/ast/Application.h"
#include "Stage_Manager.h"
#include "Stage_Factory.h"
#include "view/View.h"

class Application{

public:
    infra::Event_Bus eventbus_; // GLOBAL
    Application(const infra::ast::Application &a, const std::string &path);
private:
    // std::shared_ptr<TODO> control;
    std::shared_ptr<view::View> view_;

    std::shared_ptr<core::Score> score_;
    core::Stage_Factory stage_factory_;
    core::Stage_Manager stage_manager_;
};

#endif //PACMAN_APPLICATION_H