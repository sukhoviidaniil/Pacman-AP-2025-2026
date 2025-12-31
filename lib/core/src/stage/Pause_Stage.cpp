/***************************************************************
 * Project:       Pacman
 * File:          Pause_Stage.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-31
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

#include "core/stage/Pause_Stage.h"

#include "control/C_Pause.h"
#include "infra/event/events/game.h"
#include "infra/event/events/window.hpp"
#include "view/presentation/layout_engine/Button.h"
#include "view/presentation/layout_engine/LivesLabel.h"
#include "view/presentation/layout_engine/ScoreLabel.h"
#include "view/presentation/layout_engine/V_HBox.h"

namespace core::stg {
    Pause_Stage::~Pause_Stage() = default;

    Pause_Stage::Pause_Stage(
        const std::shared_ptr<infra::event::Event_Bus> &global_eventbus,
        const infra::Const_Score score) : Stage(global_eventbus), score_(score){

        // 0. Buttons
        std::string сontinue_b_text = "Continue";
        std::string exit_b_text = "Exit the game ";

        std::vector<infra::menu::MenuButton> buttons;
        buttons.push_back(infra::menu::MenuButton(
            сontinue_b_text,
            std::make_unique<
                infra::event::EventInstance<infra::event::game::Request_ExitPause>
            >(infra::event::game::Request_ExitPause())
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



        //1 Create a root container
        ui_root_ = std::make_unique<view::ui::VBox>();


        //
        const auto top  = std::make_shared<view::ui::UIElement>();
        const auto middle = std::make_shared<view::ui::HBox>();
        const auto bottom  = std::make_shared<view::ui::UIElement>();
        top->flex  = 1.f;
        middle->flex = 10.f;
        bottom->flex  = 1.f;

        middle->align = infra::ui::Align::Center;
        ui_root_->add(top);
        ui_root_->add(middle);
        ui_root_->add(bottom);

        //

        const auto m_left  = std::make_shared<view::ui::UIElement>();
        const auto m_middle = std::make_shared<view::ui::VBox>();
        const auto m_right  = std::make_shared<view::ui::VBox>();
        middle->add(m_left);
        middle->add(m_middle);
        middle->add(m_right);
        m_left->flex  = 1.f;
        m_middle->flex = 5.f;
        m_right->flex  = 5.f;

        //

        m_middle->add(
            std::make_shared<view::ui::Button>(
                сontinue_b_text,
                30,
                infra::ui::Color(10, 55, 55),
                infra::ui::Color(255, 255, 255),
                1
                )
            );

        m_middle->add(
            std::make_shared<view::ui::Button>(
                exit_b_text,
                30,
                infra::ui::Color(10, 55, 55),
                infra::ui::Color(255, 255, 255),
                1
                )
            );


        //

        const auto score_view = std::make_shared<view::ui::ScoreLabel>();
        const auto lives_view = std::make_shared<view::ui::LivesLabel>();

        m_right->add(score_view);
        m_right->add(lives_view);
        score_view->flex = 1.f;
        score_view->fontSize = 30;
        lives_view->flex  = 1.f;
        lives_view->fontSize = 30;



        controller = std::make_unique<control::C_Pause>(menu_);
    }

    void Pause_Stage::run(float tick) {
        dispatch(controller->event_store_);
    }

    view::ui::RenderFrame Pause_Stage::get_RenderFrame(const infra::math::Vector2 &screen_size, const bool redraw) const {
        //4 Measurement and layout of the entire tree
        ui_root_->measure(screen_size);

        //5 Preparing RenderFrame and context
        ui_root_->layout({0, 0, screen_size.x, screen_size.y});

        //6 Collecting RenderItems
        view::ui::RenderFrame frame;
        const infra::menu::MenuView v_menu(*menu_);
        const view::ViewContext ctx(redraw, &v_menu, &score_, nullptr, nullptr);
        ui_root_->append_render_items(frame, ctx);
        return frame;
    }
}
