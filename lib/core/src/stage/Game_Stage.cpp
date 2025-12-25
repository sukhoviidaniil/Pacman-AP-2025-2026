/***************************************************************
 * Project:       Pacman
 * File:          Game_Stage.cpp
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

#include "core/stage/Game_Stage.h"

#include "view/presentation/layout_engine/Map.h"
#include "view/presentation/layout_engine/V_HBox.h"


namespace core {
    Game_Stage::~Game_Stage() = default;

    Game_Stage::Game_Stage(
        const std::shared_ptr<infra::event::Event_Bus> &global_eventbus,
        const std::shared_ptr<model::Model> &model) :
        Stage(global_eventbus), model_(model){
        //1 Create a root horizontal container
        ui_root_ = std::make_shared<view::ui::VBox>();
        const auto left_col   = std::make_shared<view::ui::UIElement>();
        const auto middle_col = std::make_shared<view::ui::UIElement>();
        const auto right_col  = std::make_shared<view::ui::UIElement>();

        // 2 Add three columns
        left_col->flex   = 1.f;
        middle_col->flex = 10.f;
        right_col->flex  = 1.f;
        ui_root_->add(left_col);
        ui_root_->add(middle_col);
        ui_root_->add(right_col);

        //3 Create a UIElement for the model
        const auto model_view_ui = std::make_shared<view::ui::Map>();
        middle_col->add(model_view_ui);
    }

    void Game_Stage::run(float tick) {
        model_->run(tick);
    }

    view::ui::RenderFrame Game_Stage::get_RenderFrame(const infra::math::Vector2 &screen_size, const bool redraw) const {
        //4 Measurement and layout of the entire tree
        ui_root_->measure(screen_size);
        //5 Preparing RenderFrame and context
        ui_root_->layout({0, 0, screen_size.x, screen_size.y});
        view::ui::RenderFrame frame;
        //6 Collecting RenderItems
        const model::ui::ModelView mv(*model_);
        const view::ViewContext ctx(redraw, nullptr, &mv);
        ui_root_->append_render_items(frame, ctx);
        return frame;
    }
}
