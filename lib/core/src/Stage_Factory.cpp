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

#include "core/stage/Death_Stage.h"
#include "infra/internal/Score.h"
#include "core/stage/Level_Stage.h"
#include "core/stage/Pause_Stage.h"
#include "core/stage/Start_Stage.h"
#include "infra/diagnostics/Logger.h"
#include "infra/internal/Random.h"
#include "model/collision/Separating_Axis_Theorem.h"

namespace core {

    Stage_Factory::Stage_Factory(
        const infra::ast::ScoreBord& bord,
        std::vector<infra::ast::Model> models,
        const std::shared_ptr<infra::event::Event_Bus> &g_eventbus,
        const bool random_model_order) :
        random_model_order_(random_model_order), models_variants_(std::move(models)), g_eventbus_(g_eventbus)
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

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_Pause_Stage() {
        infra::Const_Score s(*score_);
        return std::make_shared<core::stg::Pause_Stage>(g_eventbus_, s);
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_Level_Stage() {
        infra::Const_Score s(*score_);
        return std::make_shared<core::stg::Level_Stage>(g_eventbus_, current_model_, s);
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_Death_Stage() {
        if (score_ == nullptr) {
            std::string err = "make_Death_Stage - score_ == nullptr";
            LOG(err);
            throw std::runtime_error(err);
        }
        if (score_->lives_remaining() <=0 ) {
            return make_GameOver_Stage();
        }
        infra::Const_Score s(*score_);
        return std::make_unique<stg::Death_Stage>(g_eventbus_, s);
    }

    std::shared_ptr<core::stg::Stage> Stage_Factory::make_GameOver_Stage() {
    }

    void Stage_Factory::make_new_Model() {
        const infra::ast::Model& model_variant = models_variants_[selected_model_];
        std::unique_ptr<model::collision::Separating_Axis_Theorem> cc = std::make_unique<model::collision::Separating_Axis_Theorem>();

        std::vector<std::shared_ptr<model::entity::Coin>> coins {};
        std::vector<std::shared_ptr<model::entity::PowerPellet>> pp {};
        if (current_model_ != nullptr) {
            if (current_model_->all_coins_collected()) {
                if (!random_model_order_) {
                    // next sequential model
                    selected_model_ = (selected_model_ + 1) % models_variants_.size();
                } else {
                    // random model index
                    selected_model_ = static_cast<size_t>(
                        RAND_INT(0, static_cast<int>(models_variants_.size()) - 1)
                    );
                }
            }else {
                coins = current_model_->coins_;
                pp = current_model_->power_pellets_;
            }
        }
        current_model_ = std::make_shared<model::Model>(model_variant, score_, std::move(cc), coins, pp);
    }

    void Stage_Factory::make_new_Score() {
        score_ = score_bord_->create_score();
    }
}
