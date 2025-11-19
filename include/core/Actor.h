/***************************************************************
 * Project:       Pacman
 * File:          Actor.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-17
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
#ifndef PACMAN_ACTOR_H
#define PACMAN_ACTOR_H
#include "Entity.h"
#include "logic/collision/Collision_Control.h"

namespace Core {
    class Actor : public Entity {

        Math::Vector2 current_direction_;
        Math::Vector2 next_dir_;
        float speed_ = 1.0;
        public:

        explicit Actor(const Math::Vector2 &position, const Math::Vector2 &direction, float speed);
        void move(float deltaTime, Logic::Collision::Collision_Control &collision_control);
        void set_direction(const Math::Vector2 &direction);
    };
}
#endif //PACMAN_ACTOR_H
