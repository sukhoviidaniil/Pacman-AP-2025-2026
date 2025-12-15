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

namespace infra{

    inline Event_Bus::Subscription::Subscription(
        std::shared_ptr<Event_Bus> bus,
        const std::type_index type,
        const HandlerId id
        ) : bus_(std::move(bus)), type_(type), id_(id){

    }

    inline void Event_Bus::Subscription::unsubscribe()  {
        if (bus_) {
            bus_->unsubscribe(type_, id_);
            bus_ = nullptr;
        }
    }

    inline Event_Bus::Subscription::~Subscription()  {
        unsubscribe();
    }

    inline Event_Bus::Subscription::Subscription(Subscription &&other) noexcept {
        *this = std::move(other);
    }

    inline Event_Bus::Subscription & Event_Bus::Subscription::operator=(Subscription &&other) noexcept {
        unsubscribe();
        bus_  = other.bus_;
        type_ = other.type_;
        id_   = other.id_;
        other.bus_ = nullptr;
        return *this;
    }

    inline void Event_Bus::unsubscribe(std::type_index type, HandlerId id) {
        auto it = handlers_.find(type);
        if (it == handlers_.end()) return;

        auto& list = it->second;
        list.erase(
            std::remove_if(list.begin(), list.end(),
                [id](const Handler& h) { return h.id == id; }),
            list.end()
        );
    }

    template<typename Event>
    Event_Bus::Subscription Event_Bus::subscribe(std::function<void(const Event &)> fn, int priority) {
        auto& list = handlers_[typeid(Event)];
        HandlerId id = next_id_++;

        list.push_back({
            id,
            priority,
            [fn](const void* e) {
                fn(*static_cast<const Event*>(e));
            }
        });

        std::sort(list.begin(), list.end(),
            [](const Handler& a, const Handler& b) {
                return a.priority < b.priority;
            }
        );

        return { shared_from_this(), typeid(Event), id };
    }

    template<typename Event>
    void Event_Bus::emit(const Event &event) {
        auto it = handlers_.find(typeid(Event));
        if (it == handlers_.end()) return;

        // copy — so that you can safely unsubscribe inside the callback
        auto handlers_copy = it->second;
        for (auto& h : handlers_copy) {
            h.fn(&event);
        }
    }
}
