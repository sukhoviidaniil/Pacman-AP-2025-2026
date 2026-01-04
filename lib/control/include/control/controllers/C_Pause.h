/***************************************************************
 * Project:       Pacman
 * File:          C_Pause.h
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
#ifndef PACMAN_C_PAUSE_H
#define PACMAN_C_PAUSE_H
#include "C_Menu.h"

namespace control {
    class C_Pause : public C_Menu {
    public:
        explicit C_Pause(const std::shared_ptr<infra::menu::Menu>& menu);
    };
}

#endif //PACMAN_C_PAUSE_H