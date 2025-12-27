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
#include "../../infra/include/infra/internal/Delta_Timer.h"
#include "infra/diagnostics/Logger.h"
#include "infra/event/events/window.hpp"

namespace core {
    Game::~Game() = default;

    Game::Game(
        const infra::ast::Game &a,
        const std::string &path,
        const std::shared_ptr<infra::event::Event_Bus>& eventbus
        )
    {

        set_global(eventbus);
        score_ = std::make_shared<infra::Score>();
        stage_manager_.set_stage_factory(std::make_unique<core::Stage_Factory>(g_eventbus_, score_, a.models));

        // Make View and Event_Collector
        core::View_Collector_Factory vcf;
        view_ = vcf.make_View(a.view, path);
        view_->track_global(g_eventbus_);
        event_collector_ = vcf.make_Event_Collector(a.event_collector);
    }

    void Game::set_global(const std::shared_ptr<infra::event::Event_Bus>& eventbus) {
        un_track_all();
        g_eventbus_ = eventbus;
        // TODO subs
        track(
            eventbus->subscribe<infra::event::window::Closed>(
                [this](const infra::event::window::Closed&) {
                    running_ = false;
                }
            )
        );
    }

    void Game::dispatch_events() const {

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
            const std::shared_ptr<Stage> current_stage = stage_manager_.get_top();
            current_stage->run(delta);
            infra::math::Vector2 screen_size = view_->screen_size();
            view::ui::RenderFrame v  = current_stage->get_RenderFrame(screen_size, true);
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


