/***************************************************************
 * Project:       Pacman
 * File:          Events.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-17
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
#ifndef PACMAN_EVENTS_H
#define PACMAN_EVENTS_H
#include <cstdint>
#include <typeindex>
#include <vector>

namespace infra::event {
    enum class EventMask : std::uint32_t {
        None   = 0,        // 0000
        Input  = 1 << 0,   // 0001
        Window = 1 << 1,   // 0010
        Game   = 1 << 2,   // 0100
    };

    inline EventMask operator&(EventMask a, EventMask b) {
        return static_cast<EventMask>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    struct EventConcept {
        virtual ~EventConcept() = default;
        virtual EventMask mask() const = 0;
        virtual std::type_index type() const = 0;
    };

    template<typename Event>
    struct EventInstance final : EventConcept {
        Event value;

        explicit EventInstance(Event v) : value(std::move(v)) {}

        EventMask mask() const override {
            return Event::mask;
        }

        std::type_index type() const override {
            return typeid(Event);
        }
    };
}

#endif //PACMAN_EVENTS_H