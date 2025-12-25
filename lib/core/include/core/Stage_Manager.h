/***************************************************************
 * Project:       Pacman
 * File:          Stage_Manager.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-26
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
#ifndef PACMAN_STAGE_MANAGER_H
#define PACMAN_STAGE_MANAGER_H

#include "Stage_Factory.h"
#include "infra/event/Observer.h"

#include <memory>
#include <stack>

namespace core {
    class Stage_Manager : public infra::event::Observer {

    public:
        ~Stage_Manager() override;
        explicit Stage_Manager();

        void set_stage_factory(core::Stage_Factory stage_factory);
        virtual void track_global(const std::shared_ptr<infra::event::Event_Bus>& bus);

        std::shared_ptr<core::Stage> get_top();
    protected:
        void pop_stage();
        void push_stage(const std::shared_ptr<core::Stage> &stage);
    private:

        bool track = false;
        bool complete = false;
        core::Stage_Factory stage_factory_;
        std::stack<std::shared_ptr<core::Stage>> current_stages_;
    };
}

#endif //PACMAN_STAGE_MANAGER_H