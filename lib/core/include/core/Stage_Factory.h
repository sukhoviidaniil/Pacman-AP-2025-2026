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
            infra::ast::ScoreSetup score_setup,
            const infra::ast::ScoreBord& bord,
            std::vector<infra::ast::Model> models,
            const std::shared_ptr<infra::event::Event_Bus>& g_eventbus
            );

        std::shared_ptr<core::stg::Stage> make_Start_Stage();
        std::shared_ptr<core::stg::Stage> make_pause_stage();
        std::shared_ptr<core::stg::Stage> make_new_Game_Stage();

        std::shared_ptr<core::stg::Stage> make_next_Game_Stage();

        std::shared_ptr<core::stg::Stage> make_continuing_Game_Stage();
        std::shared_ptr<core::stg::Stage> make_win_stage();
        std::shared_ptr<core::stg::Stage> make_death_stage();

    protected:

        void make_new_score();
        void select_new_model();

    private:

        // Score
        infra::ast::ScoreSetup score_setup_; /// OWNER
        std::shared_ptr<infra::ScoreBord> score_bord_ = nullptr; /// OWNER || GIVER
        std::shared_ptr<infra::Score> score_ = nullptr; /// OWNER || GIVER
        // Model
        std::shared_ptr<model::Model> current_model_ = nullptr; /// OWNER || GIVER
        bool random_model_order_ = false;
        size_t selected_model_ = 0;
        std::vector<infra::ast::Model> models_variants_; /// OWNER
        // Event Bus
        std::shared_ptr<infra::event::Event_Bus> g_eventbus_ = nullptr; /// GLOBAL || NOT OWNER
    };
}

#endif //PACMAN_STAGE_FACTORY_H