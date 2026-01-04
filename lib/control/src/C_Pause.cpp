/***************************************************************
 * Project:       Pacman
 * File:          C_Pause.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-31
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

#include "../include/control/controllers/C_Pause.h"

#include "infra/event/events/game.h"
#include "infra/event/events/input_Keyboard.h"

namespace control {
    C_Pause::C_Pause(const std::shared_ptr<infra::menu::Menu>& menu) {
        menu_ = menu;
        using namespace infra::event::input;

        bind<KeyPressed>([this](const KeyPressed& e)
        {
            switch (e.key) {
                case Key::W:
                case Key::Up:
                case Key::A:
                case Key::Left:
                    menu_->move(-1);
                    break;

                case Key::S:
                case Key::Down:
                case Key::D:
                case Key::Right:
                    menu_->move(1);
                    break;

                case Key::Enter:
                case Key::Space:
                    push_current_button_event();
                    break;

                case Key::Escape:
                    event_store_.push(infra::event::game::Request_ExitPause());
                    break;

                default: break;
            }
        }
        );
    }
}
