/***************************************************************
 * Project:       Pacman
 * File:          Event_Store.h
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
#ifndef PACMAN_EVENT_STORE_H
#define PACMAN_EVENT_STORE_H
#include <memory>
#include <vector>

#include "Event.h"

namespace infra::event {
    class Event_Store {
    public:
        std::size_t size() const noexcept;

        bool empty() const noexcept;

        bool is(std::size_t i, std::type_index t) const;

        bool matches(std::size_t i, EventMask mask) const;

        template<typename Event>
        void push(Event e);

        template<class Event>
        Event pop();

        const EventConcept &peek() const;

        const EventConcept& at(std::size_t i) const;

        template<typename Event>
        const Event& get(std::size_t i) const;
    private:
        std::vector<std::unique_ptr<EventConcept>> events_;
    };
}

#endif //PACMAN_EVENT_STORE_H