/***************************************************************
 * Project:       Pacman
 * File:          Event_Bus.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-14
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
#ifndef PACMAN_EVENT_BUS_H
#define PACMAN_EVENT_BUS_H

#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <cstdint>

#include "Event.h"

namespace infra::event {

    class Event_Bus : public std::enable_shared_from_this<Event_Bus>{
    public:
        using HandlerId = std::uint64_t;

        // ---------- Subscription handle ----------
        class Subscription {
        public:
            Subscription() = default;

            Subscription(std::shared_ptr<Event_Bus> bus,
                         std::type_index type,
                         HandlerId id);

            void unsubscribe();

            ~Subscription();

            Subscription(const Subscription&) = delete;
            Subscription& operator=(const Subscription&) = delete;

            Subscription(Subscription&& other) noexcept;

            Subscription& operator=(Subscription&& other) noexcept;

        private:
            std::shared_ptr<Event_Bus> bus_ = nullptr;
            std::type_index type_{typeid(void)};
            HandlerId id_ = 0;
        };

        // ---------- Subscribe ----------
        template<typename Event>
        Subscription subscribe(std::function<void(const Event&)> fn, int priority = 0);

        // ---------- Emit ----------
        template<typename Event>
        void emit(const Event& event);

        void emit(const EventConcept& e);

    private:
        struct Handler {
            HandlerId id;
            int priority;
            EventMask mask;
            std::function<void(const EventConcept&)> fn;
        };

        void unsubscribe(std::type_index type, HandlerId id);

        static void sort(std::vector<Handler>& list);

        std::unordered_map<std::type_index, std::vector<Handler>> handlers_;
        HandlerId next_id_ = 1;
    };
}

#include "Event_Bus.inl"

#endif //PACMAN_EVENT_BUS_H