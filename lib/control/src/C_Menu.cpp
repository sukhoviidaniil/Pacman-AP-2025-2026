/***************************************************************
 * Project:       Pacman
 * File:          C_Menu.cpp
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

#include "control/C_Menu.h"

#include "infra/event/events/input_Keyboard.h"
#include "menu/Menu.h"

namespace control {
    C_Menu::C_Menu(std::shared_ptr<Menu> menu)
    : menu_(std::move(menu))
    {
        using namespace infra::event::input;

        bind<KeyPressed>([this](const KeyPressed& e) {
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

                default: break;
            }
        });
    }

    void C_Menu::push_current_button_event() {
        if (!menu_) return;
        const auto& btn = menu_->get_current_button();
        if (btn.event) {
            // Copy the button event to the controller's event_store_
            event_store_.push_concept(*btn.event);
        }
    }
}
