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

#include "logic/Tile_Grid.h"
#include "logic/collision/World_Collision_Manager.h"

namespace Logic::Model{
    Actor::Actor(
        const std::string &name, const Math::Vector2 &position,
        const std::shared_ptr<Collision::HitBoxe> &hitbox, const unsigned int max_status,
        const Math::Vector2 &current_direction, const float speed
        ):
        Entity(name, position, hitbox, max_status), current_direction_(current_direction), speed_(speed)
    {
        if (current_direction_.length() == 0.0f) {
            current_direction_ = Math::Vector2(1.0f, 0.0f);
        }
        next_dir_ = current_direction_;
    }

    Math::Vector2 Actor::get_direction() const {
        return current_direction_;
    }

    void Actor::set_direction(const Math::Vector2 &direction) {
        next_dir_ = direction;
        next_dir_.normalize();
    }

    void Actor::move(
        const float deltaTime,
        const std::shared_ptr<Collision::World_Collision_Manager> &collision_control
        ) {

        std::shared_ptr<Tile_Grid> grid = collision_control->get_grid();

        if (speed_ == 0.0f || current_direction_.length() == 0.0f) return;

        float remaining_time = deltaTime;

        while (remaining_time > 0.0f) {
            // 1. Calculate the next integer coordinate on the path current_dir
            Math::Vector2 next_cell = grid->get_next_tile_center(position_, current_direction_);

            // 2. Calculate the maximum possible displacement to this coordinate
            Math::Vector2 to_cell = next_cell - position_;
            float dist_to_cell = to_cell.length();
            float max_move = speed_ * remaining_time;
            const float move_dist = std::min(dist_to_cell, max_move);

            const Math::Vector2 displacement = current_direction_ * move_dist;

            // 3. Create a temporary hitbox
            std::shared_ptr<Collision::HitBoxe> hit_boxe = get_hitboxe()->clone();
            hit_boxe->move_to(position_ + displacement);

            // 4. Checking for collisions
            if (collision_control->collision_world(hit_boxe)) {
                break;
            }

            // 5 Update position
            position_ += displacement;

            // 6. If you have reached the center of the cell and there is a new direction
            if (std::abs(move_dist - dist_to_cell) < 1e-6f) {
                if ((next_cell.x - position_.x) < 1e-4f && (next_cell.y - position_.y) < 1e-4f) {
                    position_ = next_cell;
                    if (next_dir_.length()>1) {
                        current_direction_ = next_dir_;
                    }
                }
            }

            // 7 Update the hitbox position
            get_hitboxe()->move_to(position_);

            // 8. Subtract the time used
            remaining_time -= move_dist / speed_;
        }
    }

    void Actor::simulate(float deltaTime, const std::shared_ptr<Collision::World_Collision_Manager> &collision_control) {
        move(deltaTime, collision_control);
    }
}
