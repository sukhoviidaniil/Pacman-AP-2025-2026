/***************************************************************
 * Project:       Pacman
 * File:          Event_Bus.cpp
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
#pragma once
#include "Event.h"

namespace infra::event{
    template<typename Event>
    Event_Bus::Subscription Event_Bus::subscribe(std::function<void(const Event &)> fn, int priority) {
        auto& list = handlers_[typeid(Event)];
        HandlerId id = next_id_++;

        list.push_back({
            id,
            priority,
            Event::mask,
            [fn = std::move(fn)](const EventConcept& e) {
                fn(static_cast<const EventInstance<Event>&>(e).value);
            }
        });

        std::sort(list.begin(), list.end(),
            [](const Handler& a, const Handler& b) {
                return a.priority < b.priority;
            }
        );

        sort(list);

        return { shared_from_this(), typeid(Event), id };
    }

    template<typename Event>
    void Event_Bus::emit(const Event &event) {
        auto it = handlers_.find(typeid(Event));
        if (it == handlers_.end()) {
            return;
        }
        for (const Handler& h : it->second) {
            h.fn(&event);
        }
    }
}
