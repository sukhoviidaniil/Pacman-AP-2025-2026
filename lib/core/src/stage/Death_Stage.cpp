/***************************************************************
 * Project:       Pacman
 * File:          Death_Stage.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-03
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

#include "core/stage/Death_Stage.h"

#include "infra/event/events/game.h"
#include "view/presentation/layout_engine/LivesLabel.h"
#include "view/presentation/layout_engine/ScoreLabel.h"
#include "view/presentation/layout_engine/SpriteElement.h"
#include "view/presentation/layout_engine/V_HBox.h"

namespace core::stg {
    Death_Stage::Death_Stage(
        const std::shared_ptr<infra::event::Event_Bus> &global_eventbus,
        const infra::Const_Score score) : Stage(global_eventbus), score_(score){

        //1 Create a root container
        ui_root_ = std::make_unique<view::ui::VBox>();

        const auto middle = std::make_shared<view::ui::SpriteElement>(
            "Try Again!",
            585,
            275
            );
        const auto bottom  = std::make_shared<view::ui::HBox>();
        middle->flex = 6.f;
        bottom->flex  = 2.f;
        bottom->align = infra::ui::Align::Center;
        ui_root_->add(middle);
        ui_root_->add(bottom);

        const auto score_view = std::make_shared<view::ui::ScoreLabel>();
        const auto lives_view = std::make_shared<view::ui::LivesLabel>();
        score_view->flex = 1.f;
        score_view->fontSize = 24;
        lives_view->flex  = 1.f;
        lives_view->fontSize = 24;
        bottom->add(score_view);
        bottom->add(lives_view);

        controller = nullptr;
    }

    void Death_Stage::run(const float tick) {
        dispatch(event_store_);
        if (elapsed_ > 0) {
            elapsed_-=tick;
        }else {
            std::unique_ptr<infra::event::EventInstance<infra::event::game::Request_Continuing_LevelStage>> event =
                std::make_unique<infra::event::EventInstance<infra::event::game::Request_Continuing_LevelStage>>(infra::event::game::Request_Continuing_LevelStage());
            event_store_.push_concept(*event);
        }
    }

    view::ui::RenderFrame Death_Stage::get_RenderFrame(const infra::math::Vector2 &screen_size, bool redraw) const {

        //4 Measurement and layout of the entire tree
        ui_root_->measure(screen_size);

        //5 Preparing RenderFrame and context
        ui_root_->layout({0, 0, screen_size.x, screen_size.y});

        //6 Collecting RenderItems
        view::ui::RenderFrame frame;
        const view::ViewContext ctx(redraw, nullptr, &score_, nullptr, nullptr);
        ui_root_->append_render_items(frame, ctx);
        return frame;

    }
}
