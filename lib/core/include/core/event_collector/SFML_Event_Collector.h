/***************************************************************
 * Project:       Pacman
 * File:          SFML_Event_Collector.h
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
#ifndef PACMAN_SFML_EVENT_COLLECTOR_H
#define PACMAN_SFML_EVENT_COLLECTOR_H
#include "Event_Collector.h"
#include "SFML/Window/Event.hpp"
#include "view/sfml/ISFML_Event_Source.h"

namespace core {
    class SFML_Event_Collector : public Event_Collector {
    public:
        explicit SFML_Event_Collector(view::ISFML_Event_Source& source);

        void collect() override;

    private:
        void dispatch(const sf::Event& e);

        view::ISFML_Event_Source& source_;
    };
}

#endif //PACMAN_SFML_EVENT_COLLECTOR_H
