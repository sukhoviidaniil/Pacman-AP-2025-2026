/***************************************************************
 * Project:       Pacman
 * File:          Ghost.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-16
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
#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include "model/entity/Actor.h"

namespace model::entity {
    class Ghost : public Actor {
    public:
        ~Ghost() override;

    };
}

#endif //PACMAN_GHOST_H