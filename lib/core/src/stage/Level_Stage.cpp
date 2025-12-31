/***************************************************************
 * Project:       Pacman
 * File:          Level_Stage.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-24
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

#include "core/stage/Level_Stage.h"

#include "control/C_Game.h"
#include "view/presentation/layout_engine/LivesLabel.h"
#include "view/presentation/layout_engine/Map.h"
#include "view/presentation/layout_engine/ScoreLabel.h"
#include "view/presentation/layout_engine/V_HBox.h"


namespace core::stg {
    Level_Stage::~Level_Stage() = default;

    Level_Stage::Level_Stage(
        const std::shared_ptr<infra::event::Event_Bus> &global_eventbus,
        const std::shared_ptr<model::Model> &model,
        const infra::Const_Score score) :
        Stage(global_eventbus), model_(model), score_(score){

        //1 Create a root container
        ui_root_ = std::make_unique<view::ui::VBox>();

        const auto middle = std::make_shared<view::ui::Map>();
        const auto bottom  = std::make_shared<view::ui::HBox>();

        // 2 Add three columns

        middle->flex = 10.f;
        bottom->flex  = 1.f;
        bottom->align = infra::ui::Align::Center;
        ui_root_->add(middle);
        ui_root_->add(bottom);

        //3 Create a UIElement for the model
        const auto score_view = std::make_shared<view::ui::ScoreLabel>();
        const auto lives_view = std::make_shared<view::ui::LivesLabel>();
        score_view->flex = 1.f;
        score_view->fontSize = 24;
        lives_view->flex  = 1.f;
        lives_view->fontSize = 24;
        bottom->add(score_view);
        bottom->add(lives_view);

        controller = std::make_unique<control::C_Game>(model_->get_pacman());
    }

    void Level_Stage::run(const float tick) {

        model_->run(tick);
        dispatch(controller->event_store_);
        dispatch(model_->event_store_);

    }

    view::ui::RenderFrame Level_Stage::get_RenderFrame(const infra::math::Vector2 &screen_size, const bool redraw) const {
        //4 Measurement and layout of the entire tree
        ui_root_->measure(screen_size);

        //5 Preparing RenderFrame and context
        ui_root_->layout({0, 0, screen_size.x, screen_size.y});

        //6 Collecting RenderItems
        view::ui::RenderFrame frame;
        const model::ui::ModelView mv(*model_);
        const view::ViewContext ctx(redraw, nullptr, &score_, nullptr, &mv);
        ui_root_->append_render_items(frame, ctx);
        return frame;
    }
}
