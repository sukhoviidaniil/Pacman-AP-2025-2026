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

namespace Logic::Model {

    struct Actor_Info: Entity_Info {
        Math::Vector2 current_direction;
        float speed;
    };

    class Actor : public Entity {
        Math::Vector2 current_direction_;
        Math::Vector2 next_dir_ = Math::Vector2(1,0);
        float speed_ = 0.1f;
        public:

        explicit Actor(
            const std::string &name,
            const Math::Vector2 &position,
            const std::shared_ptr<Collision::HitBoxe> &hitbox,
            unsigned int max_status,
            const Math::Vector2& current_direction, float speed
            );

        [[nodiscard]] Math::Vector2 get_direction() const override;
        void set_direction(const Math::Vector2 &direction) override;

        void move(float deltaTime, const std::shared_ptr<Collision::World_Collision_Manager> &collision_control) override;

        void simulate(float deltaTime, const std::shared_ptr<Collision::World_Collision_Manager> &collision_control) override;
    };
}
#endif //PACMAN_ACTOR_H
