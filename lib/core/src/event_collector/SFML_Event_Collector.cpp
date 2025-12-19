/***************************************************************
 * Project:       Pacman
 * File:          SFML_Event_Collector.cpp
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
#include "core/event_collector/SFML_Event_Collector.h"
namespace core {
    SFML_Event_Collector::SFML_Event_Collector(view::ISFML_Event_Source &source) : source_(source) {}

    void SFML_Event_Collector::collect()  {
        sf::Event e;
        while (source_.poll_event(e)) {
            dispatch(e);
        }
    }

    void SFML_Event_Collector::dispatch(const sf::Event &e)  {
        switch (e.type) {
            case sf::Event::Closed:
                // TODO EVENT event_store_.push();
                break;
            case sf::Event::KeyPressed:
                // TODO EVENT event_store_.push();
                break;
            default:
                break;
        }
    }
}
