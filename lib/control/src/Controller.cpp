/***************************************************************
 * Project:       Pacman
 * File:          Controller.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-25
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

#include "control/Controller.h"

namespace control {
    Controller::Controller() = default;

    void Controller::handle(const infra::event::EventConcept &ev)  {
        dispatch(ev);
    }

    void Controller::dispatch(const infra::event::EventConcept &ev)  {
        auto it = handlers_.find(ev.type());
        if (it == handlers_.end())
            return;

        for (const Handler& h : it->second) {
            if ((h.mask & ev.mask()) != infra::event::EventMask::None) {
                h.fn(ev);
            }
        }
    }

    void Controller::sort(std::vector<Handler> &list)  {
        std::sort(list.begin(), list.end(),
            [](const Handler& a, const Handler& b) {
                return a.priority > b.priority;
            });
    }
}
