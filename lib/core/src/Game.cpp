/***************************************************************
 * Project:       Pacman
 * File:          Game.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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

#include "core/Game.h"

#include "core/View_Collector_Factory.h"
#include "infra/internal/Delta_Timer.h"
#include "infra/diagnostics/Logger.h"
#include "infra/event/events/game.h"
#include "infra/event/events/window.hpp"

namespace core {
    Game::~Game() = default;

    Game::Game(
        const std::shared_ptr<infra::event::Event_Bus>& eventbus,
        const  std::shared_ptr<infra::io::File_Reader>& fr,
        const infra::ast::Game &a,
        const std::string &path
        ) : fr_(fr), g_eventbus_(eventbus)
    {

        track(
            eventbus->subscribe<infra::event::window::Closed>(
                [this](const infra::event::window::Closed&) {
                    running_ = false;
                }
            )
        );

        track(
            eventbus->subscribe<infra::event::window::Request_Save_Score>(
                [this](const infra::event::window::Request_Save_Score& i) {
                    sb_->add_to_bord(i.score);
                    fr_->save_ScoreBord(sb_->save());
                }
            )
        );

        sb_ = std::make_shared<infra::ScoreBord>(a.score_bord);

        stage_manager_.set_stage_factory(std::make_unique<core::Stage_Factory>(sb_, a.models, g_eventbus_));
        stage_manager_.track_global(g_eventbus_);

        // Make View and Event_Collector
        core::View_Collector_Factory vcf;
        view_ = vcf.make_View(a.view, path);
        view_->track_global(g_eventbus_);

        event_collector_ = vcf.make_Event_Collector(a.event_collector);
        std::unique_ptr<infra::event::EventConcept> ev = std::make_unique<
            infra::event::EventInstance<infra::event::game::Request_StartStage>
        >(infra::event::game::Request_StartStage());
        g_eventbus_->emit(*ev);
    }


    void Game::run() {
        if (event_collector_ == nullptr) {
            std::string err = "The program does not have a collection of events from the environment.";
            LOG(err);
            throw std::runtime_error(err);
        }

        infra::Delta_Timer dt;
        while (running_) {
            float delta = dt.tick();
            const std::shared_ptr<stg::Stage> current_stage = stage_manager_.get_top();
            current_stage->run(delta);
            infra::math::Vector2 screen_size = view_->screen_size();
            view::ui::RenderFrame v  = current_stage->get_RenderFrame(screen_size, true);
            view_->elapsed(delta);
            view_->render(v);

            event_collector_->collect();

            while (!event_collector_->event_store_.empty()) {
                std::unique_ptr<infra::event::EventConcept> ev =  event_collector_->event_store_.pop_concept();
                if (static_cast<bool>(ev->mask() & infra::event::EventMask::Window)) {
                    g_eventbus_->emit(*ev);
                    continue;
                }
                current_stage
                        ->controller
                        ->handle(*ev);
            }
        }
    }
}


