/***************************************************************
 * Project:       Pacman
 * File:          Application.h
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
#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include "infra/Score.h"
#include "infra/ast/Application.h"
#include "view/View.h"
#include "core/event_collector/Event_Collector.h"
#include "core/Stage_Manager.h"
#include "core/Stage_Factory.h"

namespace core {
    class Application : public infra::event::Observer{
    public:
        ~Application() override;
        Application(
            const infra::ast::Application &a,
            const std::string &path,
            const std::shared_ptr<infra::event::Event_Bus>& eventbus
            );

        void set_global(const std::shared_ptr<infra::event::Event_Bus>& eventbus);
        void dispatch_events() const;
        void run();

    private:
        bool running_ = true;
        std::shared_ptr<view::View> view_; // CAN be used in Event_Collector
        std::unique_ptr<core::Event_Collector> event_collector_; // NOT event a Translator/Respondent

        std::shared_ptr<infra::Score> score_; // Go to Stage_Factory -> Stage || Saves to file
        std::shared_ptr<core::Stage_Factory> stage_factory_;
        core::Stage_Manager stage_manager_;

        std::shared_ptr<infra::event::Event_Bus> g_eventbus_ = nullptr; /// GLOBAL || NOT OWNER
    };
}


#endif //PACMAN_APPLICATION_H