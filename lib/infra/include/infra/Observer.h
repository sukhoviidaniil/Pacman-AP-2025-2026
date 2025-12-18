/***************************************************************
 * Project:       Pacman
 * File:          Observer.h
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
#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H


#include "Event_Bus.h"
namespace infra {
    class Observer {
    public:
        virtual ~Observer() = default;

    protected:
        void track(Event_Bus::Subscription&& s) {
            subs_.emplace_back(std::move(s));
        }

        void un_track_all() {
            for (auto& sub : subs_) {
                sub.unsubscribe();
            }
        }
    private:
        std::vector<Event_Bus::Subscription> subs_;
    };
}

#endif //PACMAN_OBSERVER_H