/***************************************************************
 * Project:       Pacman
 * File:          Actor.cpp
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

#include "logic/model/Actor.h"

#include <cmath>

//#include "func_next_integer_coordinate.h"

namespace Logic::Model{

    Math::Vector2 Actor::get_direction() const {
        return current_direction_;
    }

    Actor::Actor(const Math::Vector2 &position, const Math::Vector2 &direction, const float speed):
    Entity(position), current_direction_(direction), speed_(speed){
    }

    void Actor::move(
        const float deltaTime,
        const Collision::World_Collision_Manager &collision_control
        ) {

        if (speed_ == 0.0f || current_direction_.length() == 0.0f) return;

        float remaining_time = deltaTime;

        while (remaining_time > 0.0f) {
            // 1. Calculate the next integer coordinate on the path current_dir
            Math::Vector2 next_cell;
            // TODO ADD next_integer_coordinate(position_, current_direction_);

            // 2. Calculate the maximum possible displacement to this coordinate
            Math::Vector2 to_cell = next_cell - position_;
            float dist_to_cell = to_cell.length();
            float max_move = speed_ * remaining_time;
            const float move_dist = std::min(dist_to_cell, max_move);

            const Math::Vector2 displacement = current_direction_ * move_dist;

            // 3. Create a temporary hitbox
            std::shared_ptr<Collision::HitBoxe> hit_boxe = get_hitboxe()->clone();
            hit_boxe->move_to(displacement);

            // 4. Checking for collisions
            if (collision_control.collision_world(hit_boxe)) {
                break;
            }

            // 5.1 Update position
            position_ += displacement;
            // 5.2 Update the hitbox position
            get_hitboxe()->move_to(displacement);

            // 7. Subtract the time used
            remaining_time -= move_dist / speed_;

            // 6. If you have reached the center of the cell and there is a new direction


            if (std::abs(move_dist - dist_to_cell) < 1e-6f) {
                bool at_cell_center = (std::abs(std::round(position_.x) - position_.x) < 1e-4f) && (std::abs(std::round(position_.y) - position_.y) < 1e-4f);
                if (at_cell_center && next_dir_.length() > 0)
                    current_direction_ = next_dir_;
            }
        }
    }

    void Actor::set_direction(const Math::Vector2 &direction) {
        next_dir_ = direction;
        next_dir_.normalize();
    }
}
