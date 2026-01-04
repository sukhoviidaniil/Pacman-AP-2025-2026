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
#include "../Controller.h"
#include "infra/menu/Menu.h"

namespace control {
    class C_Menu : public Controller {
    public:
        C_Menu();
        explicit C_Menu(std::shared_ptr<infra::menu::Menu> menu);
    protected:
        void push_current_button_event();
        std::shared_ptr<infra::menu::Menu> menu_;
    };
}

#endif //PACMAN_C_MENU_H