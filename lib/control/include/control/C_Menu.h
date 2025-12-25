/***************************************************************
 * Project:       Pacman
 * File:          C_Menu.h
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
#ifndef PACMAN_C_MENU_H
#define PACMAN_C_MENU_H
#include "Controller.h"
#include "menu/Menu.h"

namespace control {
    class C_Menu : public Controller {
    public:
        explicit C_Menu(std::shared_ptr<Menu> menu);

        void push_current_button_event();

    private:
        std::shared_ptr<Menu> menu_;
    };

}

#endif //PACMAN_C_MENU_H