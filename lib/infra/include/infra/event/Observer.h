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
namespace infra::event {
    class Observer {
    public:
        Observer() = default;
        virtual ~Observer() {
            un_track_all();
        }

        // Copying is prohibited.
        Observer(const Observer&) = delete;
        Observer& operator=(const Observer&) = delete;

        // Allow movement
        Observer(Observer&&) noexcept = default;
        Observer& operator=(Observer&&) noexcept = default;

    protected:
        void track(Event_Bus::Subscription s) {
            subs_.push_back(std::move(s));
        }

        void un_track_all() {
            for (auto& sub : subs_) {
                sub.unsubscribe();
            }
            subs_.clear();
        }
    private:
        std::vector<Event_Bus::Subscription> subs_;
    };
}

#endif //PACMAN_OBSERVER_H