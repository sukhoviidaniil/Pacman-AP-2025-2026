/***************************************************************
 * Project:       Pacman
 * File:          MenuButton.h
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
#ifndef PACMAN_MENUBUTTON_H
#define PACMAN_MENUBUTTON_H
#include <memory>
#include <string>

#include "infra/event/Event.h"

namespace control {
    struct MenuButton {
        std::string name;
        std::unique_ptr<infra::event::EventConcept> event; // Event that should occur when clicked
    };
}

#endif //PACMAN_MENUBUTTON_H