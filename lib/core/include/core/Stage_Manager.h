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

#include "Stage.h"

#include <memory>
#include <stack>

#include "infra/event/Observer.h"

namespace core {
    class Stage_Manager : public infra::event::Observer {
    public:
        explicit Stage_Manager();
        ~Stage_Manager() override;
        void handle_PacmanDied();
        void pop_stage();
        void push_stage(const std::shared_ptr<core::Stage> &stage);
        std::shared_ptr<core::Stage> get_top();
    private:
        void track(const std::shared_ptr<core::Stage> &stage);
        std::stack<std::shared_ptr<core::Stage>> current_stages_;
    };
}

#endif //PACMAN_STAGE_MANAGER_H