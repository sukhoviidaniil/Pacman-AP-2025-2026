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
#include "infra/event/events/window.hpp"


namespace core {
    Application::~Application() = default;

    Application::Application(
        const infra::ast::Application &a,
        const std::string &path,
        const std::shared_ptr<infra::event::Event_Bus>& eventbus
        ) {
        eventbus_g_ = eventbus;
        eventbus_g_->subscribe<infra::event::window::Closed>(
            [this](const infra::event::window::Closed&) {
                running_ = false;
            }
        );

        // Make new Local Event_Bus
        eventbus_l_ = std::make_shared<infra::event::Event_Bus>();

        // Make Stage_Factory and Stage_Manager
        stage_manager_.track_local(eventbus_l_);
        core::Stage_Factory sf = core::Stage_Factory(eventbus_l_, score_, a.models);
        stage_manager_.set_stage_factory(sf);

        // Make Score
        score_ = std::make_shared<core::Score>();
        score_->track_local(eventbus_l_);

        // Make View and Event_Collector
        core::View_Collector_Factory vcf;
        view_ = vcf.make_View(a.view, path);
        view_->track_local(eventbus_l_);
        event_collector_ = vcf.make_Event_Collector(a.event_collector);
    }

    void Application::set_global(const std::shared_ptr<infra::event::Event_Bus>& eventbus) {
        eventbus_g_ = eventbus;
    }

    void Application::dispatch_events() const {
        if (event_collector_ == nullptr) {
            return;
        }
        event_collector_->collect();
        while (!event_collector_->event_store_.empty()) {
            std::unique_ptr<infra::event::EventConcept> c =  event_collector_->event_store_.pop_concept();
            eventbus_g_->emit(*c);
        }
    }

    void Application::run() {
        infra::Delta_Timer dt;
        while (running_) {
            float delta = dt.tick();
            std::shared_ptr<Stage> current_stage = stage_manager_.get_top();
            current_stage->run(delta);
        }
    }
}


