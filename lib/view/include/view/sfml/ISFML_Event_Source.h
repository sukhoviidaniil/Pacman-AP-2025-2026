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

    /**
     * @brief Provides SFML window event support within the View.
     *
     * Although a View is typically render-only, SFML_View must poll the window
     * to acquire OS-level events such as close, resize, and input. These events
     * are tied to the SFML window and cannot be accessed otherwise.
     *
     * This does not violate the separation of concerns: SFML_View only exposes
     * the raw event stream, while interpretation and reaction to events remain
     * the responsibility of the core/application layers.
     */
    class ISFML_Event_Source {
    public:
        virtual ~ISFML_Event_Source() = default;
        virtual bool poll_event(sf::Event& e) = 0;
    };
}

#endif //PACMAN_ISFML_EVENT_SOURCE_H