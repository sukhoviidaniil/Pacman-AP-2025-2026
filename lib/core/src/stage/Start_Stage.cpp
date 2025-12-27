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

#include "control/C_Menu.h"
#include "infra/event/events/game.h"
#include "infra/event/events/window.hpp"
#include "view/presentation/layout_engine/Button.h"
#include "view/presentation/layout_engine/ScoreBord.h"
#include "view/presentation/layout_engine/SpriteElement.h"
#include "view/presentation/layout_engine/V_HBox.h"

namespace core::stg {
    Start_Stage::~Start_Stage() = default;

    Start_Stage::Start_Stage(
        const std::shared_ptr<infra::event::Event_Bus> &globalBus,
        const infra::Const_ScoreBord sb
        ) : Stage(globalBus), sb_(sb){

        std::string play_b_text = "Play";
        std::string exit_b_text = "Exit";

        std::vector<infra::menu::MenuButton> buttons;
        buttons.push_back(infra::menu::MenuButton(
            play_b_text,
            std::make_unique<
                infra::event::EventInstance<infra::event::game::Request_NewLevelStage>
            >(infra::event::game::Request_NewLevelStage())
            )
        );
        buttons.push_back(infra::menu::MenuButton(
            exit_b_text,
            std::make_unique<
                infra::event::EventInstance<infra::event::window::Closed>
            >(infra::event::window::Closed())
            )
        );
        menu_ = std::make_shared<infra::menu::Menu>(buttons);

        auto root = std::make_unique<view::ui::VBox>();
        //root->spacing = 0.5f;
        const auto top   = std::make_shared<view::ui::UIElement>();
        const auto middle = std::make_shared<view::ui::HBox>();
        const auto bottom  = std::make_shared<view::ui::UIElement>();

        top->add(
            std::make_shared<view::ui::SpriteElement>("Pacman Logo", 840, 260)
            );

        top->flex   = 8.f;
        middle->flex = 5.f;
        bottom->flex  = 1.f;

        root->add(top);
        root->add(middle);
        root->add(bottom);

        const auto m_left = std::make_shared<view::ui::UIElement>();
        const auto m_middle = std::make_shared<view::ui::VBox>();
        const auto m_right = std::make_shared<view::ui::ScoreBord>();
        m_left->flex   = 0.1f;
        m_middle->flex = 0.5f;
        m_right->flex  = 0.4f;
        middle->add(m_left);
        middle->add(m_middle);
        middle->add(m_right);

        m_middle->add(
            std::make_shared<view::ui::Button>(
                play_b_text,
                50,
                infra::ui::Color(10, 55, 55),
                infra::ui::Color(255, 255, 255),
                1
                )
            );

        m_middle->add(
            std::make_shared<view::ui::Button>(
                exit_b_text,
                50,
                infra::ui::Color(10, 55, 55),
                infra::ui::Color(255, 255, 255),
                1
                )
            );


        // save
        ui_root_ = std::move(root);
        controller = std::make_unique<control::C_Menu>(menu_);
    }

    void Start_Stage::run(float delta) {
        dispatch(controller->event_store_);
    }

    view::ui::RenderFrame Start_Stage::get_RenderFrame(const infra::math::Vector2 &screen_size, bool redraw) const {
        //4 Measurement and layout of the entire tree
        ui_root_->measure(screen_size);

        //5 Preparing RenderFrame and context
        ui_root_->layout({0, 0, screen_size.x, screen_size.y});

        //6 Collecting RenderItems
        view::ui::RenderFrame frame;
        const infra::menu::MenuView v_menu(*menu_);
        const view::ViewContext ctx(redraw, &v_menu, nullptr, &sb_, nullptr);
        ui_root_->append_render_items(frame, ctx);
        return frame;
    }
}
