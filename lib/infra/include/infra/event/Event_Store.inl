/***************************************************************
 * Project:       Pacman
 * File:          Event_Store.inl
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-18
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

#include "Event_Store.h"

namespace infra::event {


    template<typename Event>
    void Event_Store::push(Event e) {
        static_assert(
            requires { Event::mask; },
            "Event must define static constexpr EventMask mask"
        );
        events_.emplace_back(
            std::make_unique<EventInstance<Event>>(std::move(e))
        );
    }

    template<typename Event>
    Event Event_Store::pop() {
        auto& e = *events_.back();
        auto* inst = static_cast<EventInstance<Event>*>(&e);

        Event value = std::move(inst->value);
        events_.pop_back();
        return value;
    }

    template<typename Event>
    const Event& Event_Store::get(std::size_t i) const {
        auto& e = *events_[i];
        // it is assumed that the type has already been verified
        return static_cast<const EventInstance<Event>&>(e).value;
    }
}
