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

#include "core/Stage.h"
#include "../../../infra/include/infra/internal/Score.h"
#include "model/Model.h"


namespace core {
    class Stage_Factory {
        public:
        explicit Stage_Factory(
            const std::shared_ptr<infra::event::Event_Bus>& g_eventbus,
            const std::shared_ptr<infra::Score>& score,
            const std::vector<infra::ast::Model> &models
            );

        std::shared_ptr<core::Stage> make_start_stage();
        std::shared_ptr<core::Stage> make_pause_stage();
        std::shared_ptr<core::Stage> make_game_stage();
        std::shared_ptr<core::Stage> make_win_stage();
        std::shared_ptr<core::Stage> make_death_stage();

        protected:

        [[nodiscard]] std::shared_ptr<model::Model> get_model();
        void make_new_model();

        private:

        std::shared_ptr<infra::Score> score_;
        std::shared_ptr<model::Model> current_model_ = nullptr;
        bool random_model_order_ = false;
        size_t selected_model_;
        std::vector<infra::ast::Model> models_variants_;
        std::shared_ptr<infra::event::Event_Bus> g_eventbus_ = nullptr; /// GLOBAL || NOT OWNER
    };
}

#endif //PACMAN_STAGE_FACTORY_H