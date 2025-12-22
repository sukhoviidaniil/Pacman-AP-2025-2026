/***************************************************************
 * Project:       Pacman
 * File:          Stage_Factory.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-16
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
#ifndef PACMAN_STAGE_FACTORY_H
#define PACMAN_STAGE_FACTORY_H
#include "Controller.h"
#include "../../../infra/include/infra/Score.h"
#include "model/Model.h"
#include "view/View.h"

namespace core {
    class Stage_Factory {
        public:
        Stage_Factory();
        explicit Stage_Factory(
            const std::shared_ptr<infra::event::Event_Bus>& eventbus,
            const std::shared_ptr<infra::Score>& score,
            const std::vector<infra::ast::Model> &models
            );

        protected:

        [[nodiscard]] std::shared_ptr<model::Model> get_model() const;
        void make_new_model();

        private:

        std::shared_ptr<infra::event::Event_Bus> eventbus_; // LOCAL
        std::shared_ptr<infra::Score> score_;
        std::shared_ptr<model::Model> current_model_;
        std::vector<infra::ast::Model> models_;
    };
}

#endif //PACMAN_STAGE_FACTORY_H