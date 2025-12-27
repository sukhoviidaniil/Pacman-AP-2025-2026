/***************************************************************
 * Project:       Pacman
 * File:          Start_Stage.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-27
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


#include "core/stage/Start_Stage.h"

#include "view/presentation/layout_engine/ScoreBord.h"
#include "view/presentation/layout_engine/V_HBox.h"

namespace core::stg {
    Start_Stage::~Start_Stage() = default;

    Start_Stage::Start_Stage(
        const std::shared_ptr<infra::event::Event_Bus> &globalBus,
        const infra::Const_ScoreBord sb
        ) : Stage(globalBus), sb_(sb){

        auto root = std::make_unique<view::ui::VBox>();
        root->spacing = 0.5f;
        const auto top   = std::make_shared<view::ui::UIElement>();
        const auto middle = std::make_shared<view::ui::HBox>();
        const auto bottom  = std::make_shared<view::ui::UIElement>();

        // 2 Add three columns
        top->flex   = 5.f;
        middle->flex = 10.f;
        middle->spacing = 0.5f;
        bottom->flex  = 1.f;
        root->add(top);
        root->add(middle);
        root->add(bottom);


        const auto m_left = std::make_shared<view::ui::UIElement>();
        const auto m_middle = std::make_shared<view::ui::UIElement>(); // TODO Add btns
        const auto m_right = std::make_shared<view::ui::ScoreBord>();
        top->flex   = 1.f;
        middle->flex = 5.f;
        bottom->flex  = 5.f;


        // save
        ui_root_ = std::move(root);
    }

    void Start_Stage::run(float delta) {
    }

    view::ui::RenderFrame Start_Stage::get_RenderFrame(const infra::math::Vector2 &screen_size, bool redraw) const {

    }
}
