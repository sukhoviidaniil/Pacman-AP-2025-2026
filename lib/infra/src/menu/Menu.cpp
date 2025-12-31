/***************************************************************
 * Project:       Pacman
 * File:          Menu.cpp
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

#include "infra/menu/Menu.h"

namespace infra::menu {
    Menu::Menu() =default;

    Menu::Menu(const std::vector<MenuButton> &buttons, const NavigationMode mode)
        : nav_mode_(mode), current_index_(0) {

        for (const auto& [name, ev] : buttons) {
            MenuButton btn;
            btn.name = name;
            if (ev)
                btn.event = ev->clone();
            buttons_.push_back(std::move(btn));
        }
    }

    std::size_t Menu::current_index() const  {
        return current_index_;
    }

    std::size_t Menu::size() const {
        return buttons_.size();
    }

    void Menu::move(const int delta)  {
        if (buttons_.empty()) return;
        int new_index = static_cast<int>(current_index_) + delta;
        int size_int = static_cast<int>(buttons_.size());

        switch (nav_mode_) {
            case NavigationMode::Loop:
                if (new_index < 0) new_index = size_int - 1;
                if (new_index >= size_int) new_index = 0;
                current_index_ = static_cast<std::size_t>(new_index);
                break;

            case NavigationMode::NoLoop:
                if (new_index < 0) new_index = 0;
                if (new_index >= size_int)
                    new_index = size_int - 1;
                current_index_ = static_cast<std::size_t>(new_index);
                break;
        }
    }

    const MenuButton & Menu::get_current_button() const  {
        return buttons_.at(current_index_);
    }

    const std::vector<MenuButton> & Menu::get_buttons() const  {
        return buttons_;
    }
}
