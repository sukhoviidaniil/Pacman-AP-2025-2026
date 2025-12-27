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

#include "infra/internal/Score.h"
#include "core/stage/Level_Stage.h"
#include "core/stage/Start_Stage.h"
#include "infra/diagnostics/Logger.h"

namespace core {



    Stage_Factory::Stage_Factory(
        infra::ast::ScoreSetup score_setup,
        const infra::ast::ScoreBord& bord,
        std::vector<infra::ast::Model> models,
        const std::shared_ptr<infra::event::Event_Bus> &g_eventbus) :
        score_setup_(std::move(score_setup)),
        models_variants_(std::move(models)), g_eventbus_(g_eventbus)
    {
        if (models_variants_.empty()) {
            throw std::invalid_argument("No model specified");
        }
        score_bord_ = std::make_shared<infra::ScoreBord>(bord);
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_Start_Stage() {
        infra::Const_ScoreBord sb(*score_bord_);
        return std::make_shared<core::stg::Start_Stage>(g_eventbus_, sb);
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_pause_stage() {
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_new_Game_Stage() {
        if (current_model_ != nullptr) {
            const std::string err = "";
            LOG(err);
            return make_continuing_Game_Stage();
        }
        make_new_score();
        selected_model_ = selected_model_ % models_variants_.size() ;
        infra::ast::Model& model_variant = models_variants_[selected_model_];
        current_model_ = std::make_shared<model::Model>(model_variant, score_->level());
        infra::Const_Score s(*score_);
        return std::make_shared<core::stg::Level_Stage>(g_eventbus_, current_model_, s);
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_next_Game_Stage() {
        if (current_model_ == nullptr) {
            const std::string err = "";
            LOG(err);
            return make_new_Game_Stage();
        }
        select_new_model();
        infra::ast::Model& model_variant = models_variants_[selected_model_];
        current_model_ = std::make_shared<model::Model>(model_variant, score_->level());
        infra::Const_Score s(*score_);
        return std::make_shared<core::stg::Level_Stage>(g_eventbus_, current_model_, s);
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_continuing_Game_Stage() {
        if (current_model_ == nullptr) {
            const std::string err = "";
            LOG(err);
            return make_new_Game_Stage();
        }
        infra::ast::Model& model_variant = models_variants_[selected_model_];
        current_model_ = std::make_shared<model::Model>(model_variant, score_->level(), current_model_->coins_);
        infra::Const_Score s(*score_);
        return std::make_shared<core::stg::Level_Stage>(g_eventbus_, current_model_, s);
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_win_stage() {
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_death_stage() {
    }

    void Stage_Factory::make_new_score() {
        score_ = std::make_shared<infra::Score>(score_setup_);
    }


    void  Stage_Factory::select_new_model() {
        if (random_model_order_) {
            // make rnd index
        }else {
            // Move to next index
            selected_model_ = (selected_model_+1) % models_variants_.size() ;
        }
    }
}
