/***************************************************************
 * Project:       Pacman
 * File:          MenuView.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-27
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
#ifndef PACMAN_MENUVIEW_H
#define PACMAN_MENUVIEW_H

#include "infra/menu/Menu.h"
namespace infra::menu {
    /**
     * @brief Read-only view for accessing menu presentation data.
     *
     * Provides a lightweight interface for querying information
     * needed to display a menu without modifying its state.
     */
    class MenuView {
    public:
        /**
         * @brief Constructs a view for an existing menu.
         *
         * @param menu Menu instance to observe.
         */
        explicit MenuView(const Menu& menu)
            : menu_(menu) {}

        /**
         * @brief Returns the name of the currently selected button.
         */
        [[nodiscard]] const std::string& current_button_name() const {
            return menu_.get_current_button().name;
        }

    private:
        const Menu& menu_; ///< Referenced menu
    };
}

#endif //PACMAN_MENUVIEW_H