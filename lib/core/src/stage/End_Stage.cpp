/***************************************************************
 * Project:       Pacman
 * File:          End_Stage.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-04
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

#include "core/stage/End_Stage.h"
#include "control/controllers/C_Menu.h"
#include "infra/event/events/game.h"
#include "infra/event/events/window.hpp"
#include "view/presentation/layout_engine/Button.h"
#include "view/presentation/layout_engine/LivesLabel.h"
#include "view/presentation/layout_engine/ScoreBord.h"
#include "view/presentation/layout_engine/ScoreLabel.h"
#include "view/presentation/layout_engine/SpriteElement.h"
#include "view/presentation/layout_engine/V_HBox.h"

namespace core::stg {
    End_Stage::End_Stage(const std::shared_ptr<infra::event::Event_Bus> &global_eventbus, infra::Const_Score s, infra::Const_ScoreBord sb) :
    Stage(global_eventbus), s_(s),  sb_(sb){

        std::string to_start_b_text = "To the start menu";
        std::string save_score_b_text = "Save score";
        std::string exit_b_text = "Exit";

        std::vector<infra::menu::MenuButton> buttons;
        buttons.push_back(infra::menu::MenuButton(
            to_start_b_text,
            std::make_unique<
                infra::event::EventInstance<infra::event::game::Request_StartStage>
            >(infra::event::game::Request_StartStage())
            )
        );
        buttons.push_back(infra::menu::MenuButton(
            save_score_b_text,
            std::make_unique<
                infra::event::EventInstance<infra::event::window::Request_Save_Score>
            >(infra::event::window::Request_Save_Score(s_.get_score_info()))
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

        const auto top   = std::make_shared<view::ui::SpriteElement>("Game Over!", 600, 309);
        const auto middle = std::make_shared<view::ui::HBox>();
        const auto bottom  = std::make_shared<view::ui::UIElement>();


        top->flex   = 10.f;
        middle->flex = 10.f;
        bottom->flex  = 1.f;

        root->add(top);
        root->add(middle);
        root->add(bottom);

        const auto m_left = std::make_shared<view::ui::VBox>();
        const auto m_middle = std::make_shared<view::ui::VBox>();
        const auto m_right = std::make_shared<view::ui::ScoreBord>(30);

        m_left->flex   = 0.3f;
        m_middle->flex = 0.3f;
        m_right->flex  = 0.3f;

        middle->add(m_left);
        middle->add(m_middle);
        middle->add(m_right);

        const auto score_view = std::make_shared<view::ui::ScoreLabel>();
        const auto lives_view = std::make_shared<view::ui::LivesLabel>();
        score_view->flex = 1.f;
        score_view->fontSize = 12;
        lives_view->flex  = 1.f;
        lives_view->fontSize = 12;
        m_left->add(score_view);
        m_left->add(lives_view);

        m_middle->add(
            std::make_shared<view::ui::Button>(
                to_start_b_text,
                30,
                infra::ui::Color(10, 55, 55),
                infra::ui::Color(255, 255, 255),
                1
                )
            );

        m_middle->add(
            std::make_shared<view::ui::Button>(
                save_score_b_text,
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


        // save
        ui_root_ = std::move(root);
        controller = std::make_unique<control::C_Menu>(menu_);
    }

    void End_Stage::run(float tick) {
        dispatch(controller->event_store_);
    }

    view::ui::RenderFrame End_Stage::get_RenderFrame(const infra::math::Vector2 &screen_size, bool redraw) const {
        //4 Measurement and layout of the entire tree
        ui_root_->measure(screen_size);

        //5 Preparing RenderFrame and context
        ui_root_->layout({0, 0, screen_size.x, screen_size.y});

        //6 Collecting RenderItems
        view::ui::RenderFrame frame;
        const infra::menu::MenuView v_menu(*menu_);
        const view::ViewContext ctx(redraw, &v_menu, &s_, &sb_, nullptr);
        ui_root_->append_render_items(frame, ctx);
        return frame;
    }
}
