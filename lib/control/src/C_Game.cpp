/***************************************************************
 * Project:       Pacman
 * File:          C_Game.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-25
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

#include "control/C_Game.h"

#include "infra/event/events/game.h"
#include "infra/event/events/input_Keyboard.h"

namespace control {
    C_Game::C_Game(const std::shared_ptr<model::entity::Pacman>& pacman)
        : pacman_(pacman)
    {
        // Bind keyboard input for movement keys
        bind<infra::event::input::KeyPressed>(
            [this](const infra::event::input::KeyPressed& e) {
                using namespace infra::event::input;
                if (!pacman_) return;

                switch (e.key) {
                    case Key::W:
                    case Key::Up:
                        pacman_->to_up();
                        break;

                    case Key::A:
                    case Key::Left:
                        pacman_->to_left();
                        break;

                    case Key::S:
                    case Key::Down:
                        pacman_->to_down();
                        break;

                    case Key::D:
                    case Key::Right:
                        pacman_->to_right();
                        break;

                    case Key::Escape:
                        // Add a "RequestPause" event to the controller's local event_store_
                        event_store_.push(infra::event::game::Request_EnterPause());
                        break;
                    default:
                        break; // ignore other keys
                }
            }
        );
    }
}
