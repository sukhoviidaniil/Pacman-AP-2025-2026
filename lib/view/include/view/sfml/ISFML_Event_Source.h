/***************************************************************
 * Project:       Pacman
 * File:          ISFML_Event_Source.h
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
#ifndef PACMAN_ISFML_EVENT_SOURCE_H
#define PACMAN_ISFML_EVENT_SOURCE_H
#include "SFML/Window/Event.hpp"

namespace view {
    class ISFML_Event_Source {
    public:
        virtual ~ISFML_Event_Source() = default;
        virtual bool poll_event(sf::Event& e) = 0;
    };
}

#endif //PACMAN_ISFML_EVENT_SOURCE_H