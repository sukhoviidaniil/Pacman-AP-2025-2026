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
    /**
     * @brief Base class for objects observing events from an Event_Bus.
     *
     * Manages the lifetime of event subscriptions and ensures that
     * all tracked subscriptions are properly unsubscribed on destruction.
     */
    class Observer {
    public:
        /**
         * @brief Default constructor.
         */
        Observer() = default;

        /**
         * @brief Virtual destructor.
         *
         * Automatically unsubscribes from all tracked events.
         */
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
        /**
         * @brief Tracks an event subscription.
         *
         * The subscription will be automatically unsubscribed
         * when the observer is destroyed or untracked.
         *
         * @param s Subscription to track.
         */
        void track(Event_Bus::Subscription s) {
            subs_.push_back(std::move(s));
        }

        /**
         * @brief Unsubscribes from all tracked subscriptions.
         *
         */
        void un_track_all() {
            for (auto& sub : subs_) {
                sub.unsubscribe();
            }
            subs_.clear();
        }
    private:
        /// List of tracked subscriptions
        std::vector<Event_Bus::Subscription> subs_;
    };
}

#endif //PACMAN_OBSERVER_H