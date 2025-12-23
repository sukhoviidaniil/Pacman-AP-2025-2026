/***************************************************************
 * Project:       Pacman
 * File:          Event_Collector.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-19
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
#ifndef PACMAN_EVENT_COLLECTOR_H
#define PACMAN_EVENT_COLLECTOR_H
#include "infra/event/Event_Store.h"

namespace core {
    class Event_Collector {
    public:
        virtual ~Event_Collector() = default;

        virtual void collect() = 0;
        infra::event::Event_Store event_store_;
    };
}

#endif //PACMAN_EVENT_COLLECTOR_H