/***************************************************************
 * Project:       Pacman
 * File:          C_Game.h
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
#ifndef PACMAN_C_GAME_H
#define PACMAN_C_GAME_H

#include "control/Controller.h"

namespace control {
    class C_Game : public Controller {
    public:

        C_Game(const std::shared_ptr<model::entity::Pacman>& pacman);

    private:

        std::shared_ptr<model::entity::Pacman> pacman_;
    };
}

#endif //PACMAN_C_GAME_H