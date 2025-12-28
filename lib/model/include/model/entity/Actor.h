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

#include "Entity.h"
#include "../../../../infra/include/infra/internal/Status.h"
#include "model/collision/World_Collision_Manager.h"
#include "infra/math/Direction.h"

namespace model::entity {
    class Actor : public Entity {
    public:
        ~Actor() override;

        Actor(const std::string &name, float size, const infra::math::Point2 &position,
              std::unique_ptr<collision::HitBox> hitbox, const infra::math::Direction &current_direction, float speed);

        void set_direction(const infra::math::Direction &direction);
        void to_left();
        void to_right();
        void to_up();
        void to_down();

        [[nodiscard]] infra::math::Direction get_direction() const;


        void move(float deltaTime, const collision::World_Collision_Manager &collision_control);

        void virtual act(float deltaTime, const collision::World_Collision_Manager &collision_control);

        infra::Status status_ = infra::Status::Alive;
        private:
        infra::math::Direction current_direction_;
        infra::math::Direction next_direction_;
        // m/s
        float speed_;

    private:

        void change_direction(const std::shared_ptr<Tile_Grid>& grid);


    };
}

#endif //PACMAN_ACTOR_H