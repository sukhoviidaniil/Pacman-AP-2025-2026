/***************************************************************
 * Project:       Pacman
 * File:          Actor.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-13
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

#include "model/Entity.h"
#include "model/collision/World_Collision_Manager.h"

namespace model::entity {
    class Actor : public Entity {
        Actor(
            const std::string &name,
            const math::Point2 &position,
            const std::shared_ptr<collision::HitBox> &hitbox,
            const int &max_status,
            const math::Vector2 &current_direction,
            float speed
            );

        [[nodiscard]] math::Vector2 get_direction() const;

        void set_direction(const math::Vector2 &direction);

        void move(float deltaTime, const std::shared_ptr<collision::World_Collision_Manager> &collision_control);

        void virtual act(float deltaTime, const std::shared_ptr<collision::World_Collision_Manager> &collision_control);

    private:
        math::Vector2 current_direction_;
        math::Vector2 next_direction_;
        // m/s
        float speed_;
        int status_ = 0;
        int max_status_;


    };
}

#endif //PACMAN_ACTOR_H