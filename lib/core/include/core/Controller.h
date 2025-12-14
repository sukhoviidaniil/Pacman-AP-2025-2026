/***************************************************************
 * Project:       Pacman
 * File:          Controller.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-10
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
#ifndef PACMAN_CONTROLLER_H
#define PACMAN_CONTROLLER_H

#include "SFML/Window/Event.hpp"

namespace core::control{
    class Controller {
    public:
        virtual ~Controller() = default;
        virtual void respond(const sf::Event& event) = 0;

    };
}
#endif //PACMAN_CONTROLLER_H