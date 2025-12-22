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

#include "../../../infra/include/infra/Score.h"
#include "infra/ast/Application.h"
#include "Stage_Manager.h"
#include "Stage_Factory.h"
#include "event_collector/Event_Collector .h"
#include "view/View.h"

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
        void track_global(const std::shared_ptr<infra::event::Event_Bus>& bus);
        void run();
        std::shared_ptr<infra::event::Event_Bus> eventbus_l_; // LOCAL
    private:
        bool running_ = true;

        std::unique_ptr<core::Controller> controller_;
        std::shared_ptr<view::View> view_; // Can be used in Event_Collector
        std::unique_ptr<core::Event_Collector> event_collector_;

        std::shared_ptr<core::Score> score_;
        std::shared_ptr<core::Stage_Factory> stage_factory_;
        core::Stage_Manager stage_manager_;

        std::shared_ptr<infra::event::Event_Bus> eventbus_g_ = nullptr; // GLOBAL
    };
}


#endif //PACMAN_APPLICATION_H