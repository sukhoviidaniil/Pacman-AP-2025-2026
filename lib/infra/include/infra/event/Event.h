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
#include <utility>
#include <memory>

namespace infra::event {
    /**
     * @brief Bitmask describing event categories.
     *
     * Used to classify events and allow filtering by type of origin
     * (input, window system, game logic, etc.).
     */
    enum class EventMask : std::uint32_t {
        None   = 0,        // 0000
        Input  = 1 << 0,   // 0001
        Window = 1 << 1,   // 0010
        Game   = 1 << 2,   // 0100
    };


    /**
     * @brief Bitwise AND operator for EventMask.
     *
     * Allows combining and testing flags.
     */
    inline EventMask operator&(infra::event::EventMask a, infra::event::EventMask b) {
        return static_cast<EventMask>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    /**
     * @brief Bitwise OR operator for EventMask.
     *
     * Allows combining multiple event categories.
     */
    inline EventMask operator|(EventMask a, EventMask b) {
        return static_cast<EventMask>(
            static_cast<uint32_t>(a) | static_cast<uint32_t>(b)
        );
    }

    /**
     * @brief Checks whether a flag is present in a mask.
     *
     * @param value Combined event mask.
     * @param flag  Flag to test.
     * @return true if the flag is set, false otherwise.
     */
    inline bool has(EventMask value, EventMask flag) {
        return (value & flag) != EventMask::None;
    }

    /**
     * @brief Type-erased interface for events.
     *
     * Provides a common abstraction for storing and handling
     * events of different concrete types.
     */
    struct EventConcept {
        virtual ~EventConcept() = default;
        /**
         * @brief Returns the event category mask.
         */
        [[nodiscard]] virtual infra::event::EventMask mask() const = 0;

        /**
         * @brief Returns the runtime type information of the event.
         */
        [[nodiscard]] virtual std::type_index type() const = 0;

        /**
         * @brief Returns a pointer to the stored event data.
         *
         * @note TODO: clarify expected lifetime and usage pattern.
         */
        [[nodiscard]] virtual const void* data() const = 0;

        /**
         * @brief Creates a deep copy of the event.
         */
        [[nodiscard]] virtual std::unique_ptr<EventConcept> clone() = 0;
    };

    /**
     * @brief Concrete event wrapper for a specific event type.
     *
     * @tparam Event User-defined event type.
     *
     * Wraps a concrete event value and exposes it through
     * the EventConcept interface.
     */
    template<typename Event>
    struct EventInstance final : EventConcept {
        Event value;  ///< Stored event value

        /**
         * @brief Constructs an event instance.
         *
         * @param v Event value to store.
         */
        explicit EventInstance(Event v) : value(std::move(v)) {}

        /**
         * @brief Returns the event mask defined by the event type.
         */
        [[nodiscard]] EventMask mask() const override {
            return Event::mask;
        }

        /**
         * @brief Returns the runtime type of the stored event.
         */
        [[nodiscard]] std::type_index type() const override {
            return typeid(Event);
        }

        /**
         * @brief Returns a pointer to the stored event value.
         */
        [[nodiscard]] const void* data() const override { return &value; }


        /**
         * @brief Creates a copy of this event instance.
         */
        [[nodiscard]] std::unique_ptr<infra::event::EventConcept> clone() override {
            return std::make_unique<EventInstance<Event>>(value);
        }
    };
}

#endif //PACMAN_EVENTS_H