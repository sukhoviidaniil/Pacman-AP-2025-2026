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
    /**
     * @brief Container for storing events in a type-erased form.
     *
     * Provides stack-like access to events and utilities for
     * type and mask-based inspection.
     */
    class Event_Store {
    public:
        /**
         * @brief Returns the number of stored events.
         */
        [[nodiscard]] std::size_t size() const noexcept;

        /**
         * @brief Checks whether the store is empty.
         */
        [[nodiscard]] bool empty() const noexcept;

        /**
         * @brief Checks whether the event at the given index has a specific type.
         *
         * @param i Index of the event.
         * @param t Expected type.
         */
        [[nodiscard]] bool is(std::size_t i, std::type_index t) const;

        /**
         * @brief Checks whether the event at the given index matches a mask.
         *
         * @param i Index of the event.
         * @param mask Mask to test.
         */
        [[nodiscard]] bool matches(std::size_t i, EventMask mask) const;

        /**
         * @brief Stores a concrete event.
         *
         * @tparam Event Event type.
         * @param e Event value.
         */
        template<typename Event>
        void push(Event e);

        /**
         * @brief Stores a type-erased event by cloning it.
         *
         * @param e Event concept instance.
         */
        void push_concept(EventConcept &e);


        /**
         * @brief Removes and returns the last event as a concrete type.
         *
         * @tparam Event Expected event type.
         *
         * @throws std::out_of_range if the store is empty.
         */
        template<class Event>
        Event pop();

        /**
         * @brief Removes and returns the last event as a type-erased object.
         * @throws std::out_of_range if the store is empty.
         */
        std::unique_ptr<EventConcept> pop_concept();

        /**
         * @brief Returns the last stored event without removing it.
         */
        [[nodiscard]] const EventConcept& peek() const;

        /**
         * @brief Returns the event at a specific index.
         *
         * @param i Index of the event.
         */
        [[nodiscard]] const EventConcept& at(std::size_t i) const;


        /**
         * @brief Accesses a stored event as a concrete type.
         *
         * @tparam Event Expected event type.
         * @param i Index of the event.
         *
         * @note TODO: clarify required preconditions for type safety.
         */
        template<typename Event>
        const Event& get(std::size_t i) const;
    private:
        /// Stored events
        std::vector<std::unique_ptr<EventConcept>> events_;
    };
}
#include "Event_Store.inl"

#endif //PACMAN_EVENT_STORE_H