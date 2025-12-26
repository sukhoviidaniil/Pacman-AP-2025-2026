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

#include "../../infra/include/infra/internal/Score.h"
#include "core/stage/Game_Stage.h"

namespace core {

    Stage_Factory::Stage_Factory(
        const std::shared_ptr<infra::event::Event_Bus>& g_eventbus,
        const std::shared_ptr<infra::Score> &score,
        const std::vector<infra::ast::Model> &models
        ) :  score_(score), selected_model_(0), models_variants_(models) {
        g_eventbus_ = g_eventbus;
        if (models_variants_.empty()) {
            throw std::invalid_argument("No model specified");
        }
        if (score_ == nullptr) {
            throw std::invalid_argument("Score is nullptr");
        }
    }

    std::shared_ptr<core::Stage> Stage_Factory::make_start_stage() {
    }

    std::shared_ptr<core::Stage> Stage_Factory::make_pause_stage() {
    }

    std::shared_ptr<core::Stage> Stage_Factory::make_game_stage() {
        if (current_model_ == nullptr) {
            current_model_ = get_model();
        }
        if (score_->lives_remaining == 0) {
            return make_death_stage();
        }
        std::shared_ptr<model::Model> current_model = get_model();
        auto s = std::make_shared<core::Game_Stage>(g_eventbus_, current_model);
        return s;
    }

    std::shared_ptr<core::Stage> Stage_Factory::make_win_stage() {
    }

    std::shared_ptr<core::Stage> Stage_Factory::make_death_stage() {
    }

    std::shared_ptr<model::Model> Stage_Factory::get_model(){
        if (models_variants_.empty()) {
            throw std::invalid_argument("No model specified");
        }
        if (current_model_ != nullptr) {
            // Current model exist

            if (random_model_order_) {
                // make rnd index
            }else {
                // Move to next index
                selected_model_ = (selected_model_+1) % models_variants_.size() ;
            }

            // Expect selected_model_ be in range
            infra::ast::Model& model_variant = models_variants_[selected_model_];

            // If exist coins = save them to next stage
            if (current_model_->all_coins_eaten()) {
                current_model_ = std::make_shared<model::Model>(model_variant, score_->level);
            }else {
                current_model_ = std::make_shared<model::Model>(model_variant, score_->level, current_model_->coins_);
            }
        }else {
            // Current model dont exist

            // cut index
            selected_model_ = selected_model_ % models_variants_.size() ;
            infra::ast::Model& model_variant = models_variants_[selected_model_];
            current_model_ = std::make_shared<model::Model>(model_variant, score_->level);
        }
        return current_model_;
    }

    void Stage_Factory::make_new_model() {

    }
}
