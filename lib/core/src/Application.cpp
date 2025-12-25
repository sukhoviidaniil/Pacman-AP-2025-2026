/***************************************************************
 * Project:       Pacman
 * File:          Application.cpp
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

#include "core/Application.h"

#include "core/View_Collector_Factory.h"
#include "infra/Delta_Timer.h"
#include "infra/diagnostics/Logger.h"
#include "infra/event/events/window.hpp"

namespace core {
    Application::~Application() = default;

    Application::Application(
        const infra::ast::Application &a,
        const std::string &path,
        const std::shared_ptr<infra::event::Event_Bus>& eventbus
        ) {
        set_global(eventbus);



        // Make Score
        score_ = std::make_shared<infra::Score>();



        // Make Stage_Factory and Stage_Manager
        core::Stage_Factory sf = core::Stage_Factory(g_eventbus_, score_, a.models);
        stage_manager_.set_stage_factory(sf);

        // Make View and Event_Collector
        core::View_Collector_Factory vcf;
        view_ = vcf.make_View(a.view, path);
        view_->track_global(g_eventbus_);
        event_collector_ = vcf.make_Event_Collector(a.event_collector);
    }

    void Application::set_global(const std::shared_ptr<infra::event::Event_Bus>& eventbus) {
        g_eventbus_ = eventbus;
        // TODO subs
        un_track_all();
        track(
            eventbus->subscribe<infra::event::window::Closed>(
                [this](const infra::event::window::Closed&) {
                    running_ = false;
                }
            )
        );
    }

    void Application::dispatch_events() const {



    }

    void Application::run() {
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
                        ->handle(ev);
            }

            dispatch_events();
        }
    }
}


