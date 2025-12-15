/***************************************************************
 * Project:       Pacman
 * File:          Pacman.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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
#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Actor.h"

namespace model::entity {
    class Pacman : public Actor {
    public:
        ~Pacman() override;

        void act(float deltaTime, const std::shared_ptr<collision::World_Collision_Manager> &collision_control) override;
    };
}

#endif //PACMAN_PACMAN_H