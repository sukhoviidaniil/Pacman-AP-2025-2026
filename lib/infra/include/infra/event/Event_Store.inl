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
    inline std::size_t Event_Store::size() const noexcept {
        return events_.size();
    }

    inline bool Event_Store::empty() const noexcept {
        return events_.empty();
    }

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

    inline std::unique_ptr<EventConcept> Event_Store::pop_concept() {
        if (events_.empty()) {
            // return nullptr;
            throw std::out_of_range("Event_Store is empty");
        }

        auto ptr = std::move(events_.back());
        events_.pop_back();
        return ptr;
    }

    inline const EventConcept& Event_Store::peek() const {
        return *events_.back();
    }

    inline const EventConcept& Event_Store::at(std::size_t i) const {
        return *events_[i];
    }

    template<typename Event>
    const Event& Event_Store::get(std::size_t i) const {
        auto& e = *events_[i];
        // it is assumed that the type has already been verified
        return static_cast<const EventInstance<Event>&>(e).value;
    }

    inline bool Event_Store::is(const std::size_t i, const std::type_index t) const {
        return events_[i]->type() == t;
    }

    inline bool Event_Store::matches(const std::size_t i, const EventMask mask) const {
        return static_cast<bool>(events_[i]->mask() & mask);
    }
}
