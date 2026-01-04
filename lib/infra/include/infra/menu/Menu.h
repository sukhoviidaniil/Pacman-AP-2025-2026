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
    /**
     * @brief Menu container managing a list of buttons and navigation state.
     *
     * Provides basic navigation through menu buttons and access
     * to the currently selected entry.
     */
    class Menu {
    public:
        /**
         * @brief Defines how menu navigation behaves at boundaries.
         */
        enum class NavigationMode {
            Loop, ///< Navigation wraps around at the ends
            NoLoop ///< Navigation stops at the first and last element
        };

        /**
         * @brief Constructs an empty menu.
         */
        Menu();

        /**
         * @brief Constructs a menu with predefined buttons.
         *
         * @param buttons Initial list of menu buttons.
         * @param mode Navigation behavior.
         */
        explicit Menu(const std::vector<MenuButton>& buttons, NavigationMode mode = NavigationMode::Loop);


        /**
         * @brief Returns the index of the currently selected button.
         */
        [[nodiscard]] std::size_t current_index() const;

        /**
         * @brief Returns the number of buttons in the menu.
         */
        [[nodiscard]] std::size_t size() const;


        /**
         * @brief Moves the current selection.
         *
         * @param delta Offset applied to the current index.
         *
         */
        void move(int delta);

        /**
         * @brief Returns the currently selected button.
         */
        [[nodiscard]] const MenuButton& get_current_button() const;

        /**
         * @brief Returns all menu buttons.
         */
        [[nodiscard]] const std::vector<MenuButton>& get_buttons() const;

    private:
        std::vector<MenuButton> buttons_; ///< Stored menu buttons
        NavigationMode nav_mode_; ///< Navigation behavior
        std::size_t current_index_; ///< Current selection index
    };
}

#endif //PACMAN_MENU_H