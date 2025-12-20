/***************************************************************
 * Project:       Pacman
 * File:          Stage_Factory.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-20
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

#include "core/Stage_Factory.h"

#include "core/Score.h"

namespace core {
    Stage_Factory::Stage_Factory(const std::vector<infra::ast::Model> &models) : models_(models) {

    }

    void Stage_Factory::add_Score(const std::shared_ptr<Score>& score) {
        score_ = score;
    }

    void Stage_Factory::add_View(const std::shared_ptr<view::View> &view) {
        view_ = view;
    }

    void Stage_Factory::add_Controller(const std::shared_ptr<Controller> &controller) {
        controller_ = controller;
    }

    std::shared_ptr<model::Model> Stage_Factory::get_model() const {
        return current_model_;
    }

    void Stage_Factory::make_new_model() {

    }
}
