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

#include "infra/event/events/input_Keyboard.h"
#include "infra/event/events/input_Mouse.h"
#include "infra/event/events/window.hpp"

namespace core {
    SFML_Event_Collector::SFML_Event_Collector(view::ISFML_Event_Source &source) : source_(source) {}

    void SFML_Event_Collector::collect()  {
        sf::Event event{};
        while (source_.poll_event(event)) {
            dispatch(event);
        }
    }

    void SFML_Event_Collector::dispatch(const sf::Event &e)  {
        using namespace infra::event;
        switch (e.type) {

            // ---------- Window ----------
            case sf::Event::Closed:
                event_store_.push(window::Closed{});
                break;

            case sf::Event::Resized:
                event_store_.push(window::Resized{
                    e.size.width,
                    e.size.height
                });
                break;

            case sf::Event::GainedFocus:
                event_store_.push(window::FocusGained{});
                break;

            case sf::Event::LostFocus:
                event_store_.push(window::FocusLost{});
                break;

                // ---------- Keyboard ----------
            case sf::Event::KeyPressed:
                event_store_.push(input::KeyPressed{
                    static_cast<input::Key>(e.key.code),
                    e.key.alt,
                    e.key.control,
                    e.key.shift,
                    e.key.system
                });
                break;

            case sf::Event::KeyReleased:
                event_store_.push(input::KeyReleased{
                    static_cast<input::Key>(e.key.code)
                });
                break;

                // ---------- Mouse ----------
            case sf::Event::MouseMoved:
                event_store_.push(input::MouseMoved{
                    e.mouseMove.x,
                    e.mouseMove.y
                });
                break;

            case sf::Event::MouseButtonPressed:
                event_store_.push(input::MouseButtonPressed{
                    static_cast<input::MouseButton>(e.mouseButton.button),
                    e.mouseButton.x,
                    e.mouseButton.y
                });
                break;

            case sf::Event::MouseButtonReleased:
                event_store_.push(input::MouseButtonReleased{
                    static_cast<input::MouseButton>(e.mouseButton.button),
                    e.mouseButton.x,
                    e.mouseButton.y
                });
                break;

            case sf::Event::MouseWheelScrolled:
                event_store_.push(input::MouseWheelScrolled{
                    e.mouseWheelScroll.delta,
                    e.mouseWheelScroll.x,
                    e.mouseWheelScroll.y
                });
                break;

            default:
                break;
        }
    }
}
