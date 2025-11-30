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
#include "logic/model/Entity.h"
#include "logic/collision/World_Collision_Manager.h"

namespace Logic::Model {
    class Actor : public Entity {
        Math::Vector2 current_direction_;
        Math::Vector2 next_dir_;
        float speed_ = 0.1f;
        public:

        [[nodiscard]] Math::Vector2 get_direction() const;
        explicit Actor(const Math::Vector2 &position, const Math::Vector2 &direction, float speed);

        void move(float deltaTime, const Collision::World_Collision_Manager &collision_control);
        void set_direction(const Math::Vector2 &direction);

    };
}
#endif //PACMAN_ACTOR_H
