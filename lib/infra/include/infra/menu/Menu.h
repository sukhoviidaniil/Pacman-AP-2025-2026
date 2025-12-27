/***************************************************************
 * Project:       Pacman
 * File:          Menu.h
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
#ifndef PACMAN_MENU_H
#define PACMAN_MENU_H
#include <cstddef>
#include <vector>

#include "infra/menu/MenuButton.h"

namespace infra::menu {
    class Menu {
    public:
        enum class NavigationMode {
            Loop,
            NoLoop
        };

        explicit Menu(const std::vector<MenuButton>& buttons, NavigationMode mode = NavigationMode::Loop);

        [[nodiscard]] std::size_t current_index() const;
        [[nodiscard]] std::size_t size() const;

        void move(int delta);

        [[nodiscard]] const MenuButton& get_current_button() const;

        [[nodiscard]] const std::vector<MenuButton>& get_buttons() const;

    private:
        std::vector<MenuButton> buttons_;
        NavigationMode nav_mode_;
        std::size_t current_index_;
    };
}

#endif //PACMAN_MENU_H