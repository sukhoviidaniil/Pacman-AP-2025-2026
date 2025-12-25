/***************************************************************
 * Project:       Pacman
 * File:          Controller.h
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
#ifndef PACMAN_CONTROLLER_H
#define PACMAN_CONTROLLER_H
#include "model/Model.h"

namespace control {
    /**
     * @class Controller
     *
     * @brief Base class for stage-local event controllers.
     *
     * The Controller acts as a synchronous, deterministic event dispatcher
     * for a single Stage. It receives already-collected events (typically
     * input or gameplay events) and immediately dispatches them to bound
     * handlers based on:
     *  - concrete event type
     *  - event mask
     *  - handler priority
     *
     * The Controller:
     *  - does NOT own the main event loop
     *  - does NOT store events long-term
     *  - does NOT perform rendering
     *  - does NOT communicate globally
     *
     * Its sole responsibility is to react to events and invoke domain logic.
     */
    class Controller {
    public:
        /**
         * @brief Virtual destructor.
         *
         * Required for safe polymorphic destruction.
         */
        virtual ~Controller() = default;

        /**
         * @brief Entry point for processing a single event.
         *
         * This is the only public method used by external systems
         * (e.g. Application or Stage) to forward events to the Controller.
         *
         * The method performs runtime dispatch based on the event's
         * concrete type and mask, invoking all matching handlers
         * in priority order.
         *
         * @param ev A type-erased event instance.
         *
         * @note This method is synchronous and deterministic.
         *       The event is processed immediately.
         */
        void handle(const infra::event::EventConcept& ev);

        /**
         * @brief Optional temporary event storage.
         *
         * If used, this store may contain events accumulated during a framer.
         *
         * @warning Ownership and lifetime are local to the Controller.
         *          This should NOT be used as a global or asynchronous queue.
         */
        infra::event::Event_Store event_store_;
    protected:
        /**
         * @struct Handler
         *
         * @brief Internal representation of a bound event handler.
         *
         * Each handler is associated with:
         *  - an event mask (used for filtering)
         *  - a priority (used for ordering)
         *  - a type-erased callable
         */
        struct Handler {
            infra::event::EventMask mask;   ///< Event category filter
            int priority;                   ///< Execution priority (higher = earlier)
            std::function<void(const infra::event::EventConcept&)> fn; ///< Handler function
        };

        /**
         * @brief Bind a handler function to a specific event type.
         *
         * Registers a callback that will be invoked whenever an event
         * of type `Event` is dispatched to this Controller.
         *
         * The handler will only be executed if:
         *  - the event's runtime type matches `Event`
         *  - the event mask intersects with `Event::mask`
         *
         * Handlers are sorted by priority in descending order.
         *
         * @tparam Event Concrete event type to bind.
         * @param fn Callback function accepting a const reference to Event.
         * @param priority Execution priority (higher values run first).
         *
         * @note This method is intended to be used in derived class
         *       constructors or initialization routines.
         *
         * @warning This function performs a static_cast internally.
         *          The correctness relies on the runtime type check.
         */
        template<typename Event>
        void bind(std::function<void(const Event&)> fn,
          int priority = 0) {
            auto& list = handlers_[typeid(Event)];
            list.push_back(Handler{
                Event::mask,
                priority,
                [fn](const infra::event::EventConcept& ev) {
                    fn(*static_cast<const Event*>(ev.data()));
                }
            });
            sort(list);
        }

    private:
        /**
         * @brief Dispatch an event to all matching handlers.
         *
         * Looks up handlers registered for the event's concrete type,
         * filters them by event mask, and invokes them in priority order.
         *
         * @param ev A type-erased event instance.
         */
        void dispatch(const infra::event::EventConcept& ev);

        /**
         * @brief Sort a handler list by descending priority.
         *
         * @param list List of handlers to be sorted.
         */
        static void sort(std::vector<Handler>& list);


        /**
         * @brief Mapping from event type to its registered handlers.
         *
         * Each event type has its own ordered handler list.
         */
        std::unordered_map<
            std::type_index,
            std::vector<Handler>
        > handlers_;
    };
}

#endif //PACMAN_CONTROLLER_H