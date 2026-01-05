/***************************************************************
 * Project:       Pacman
 * File:          SFML_View_Events.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-24
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


#include "view/sfml/SFML_View.h"
#include "infra/event/events/window.hpp"

namespace view {

    void SFML_View::track_local(const std::shared_ptr<infra::event::Event_Bus>& bus) {
    }

    void SFML_View::track_global(const std::shared_ptr<infra::event::Event_Bus>& bus) {
        using namespace infra::event::window;
        // Closing the window
        track(
            bus->subscribe<Closed>(
                [this](const Closed&) {
                    window_.close();
                }
            )
        );
        // Change window size
        track(
            bus->subscribe<Resized>(
                [this](const Resized& e) {
                    sf::View v = window_.getView();
                    v.setSize(static_cast<float>(e.width),
                              static_cast<float>(e.height));
                    v.setCenter(v.getSize() * 0.5f);
                    window_.setView(v);
                }
            )
        );

        // Loss/gain of focus
    }

    bool SFML_View::poll_event(sf::Event &e)  {
        return window_.pollEvent(e);
    }

    infra::math::Vector2 SFML_View::screen_size() const {
        return {static_cast<float>(window_.getSize().x), static_cast<float>(window_.getSize().y)};
    }
}
