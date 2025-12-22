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

#include "../../infra/include/infra/Score.h"

namespace core {
    Stage_Factory::Stage_Factory() = default;

    Stage_Factory::Stage_Factory(
        const std::shared_ptr<infra::event::Event_Bus> &eventbus,
        const std::shared_ptr<infra::Score> &score,
        const std::vector<infra::ast::Model> &models
        ) : eventbus_(eventbus), score_(score), models_(models) {
    }

    std::shared_ptr<model::Model> Stage_Factory::get_model() const {
        return current_model_;
    }

    void Stage_Factory::make_new_model() {

    }
}
