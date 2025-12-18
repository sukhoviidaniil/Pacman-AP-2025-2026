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

#include "model/entity/Actor.h"
#include <cmath>

#include "model/Tile_Grid.h"
#include "model/collision/World_Collision_Manager.h"

namespace model::entity{
    Actor::Actor(
        const std::string &name, const math::Point2 &position,
        const std::shared_ptr<collision::HitBox> &hitbox, const int& max_status,
        const math::Vector2 &current_direction, const float speed
        ):
        Entity(name, position, hitbox), current_direction_(current_direction), speed_(speed), max_status_(max_status)
    {
        if (current_direction_.length() == 0.0f) {
            current_direction_ = math::Vector2(1.0f, 0.0f);
        }
        next_direction_ = current_direction_;
    }

    math::Vector2 Actor::get_direction() const {
        return current_direction_;
    }

    void Actor::set_direction(const math::Vector2 &direction) {
        next_direction_ = direction;
        next_direction_.normalize();
    }

    void Actor::move(
        const float deltaTime,
        const std::shared_ptr<collision::World_Collision_Manager> &collision_control
        ) {

        const std::shared_ptr<const Tile_Grid> grid = collision_control->get_grid();

        if (speed_ == 0.0f || current_direction_.length() == 0.0f) return;

        float remaining_time = deltaTime;

        while (remaining_time > 0.0f) {
            // 1. Calculate the next tile coordinate on the path current_dir
            std::shared_ptr<const Tile> t = grid->get_next_tile(position_, current_direction_);
            if (t == nullptr) {
                throw std::invalid_argument("Not a valid tile for Actor - Actor out bounds;");
            }
            const math::Point2& next_tile_center = t->get_position();

            // 2. Calculate the maximum possible displacement to this coordinate
            auto to_cell = math::Vector2(next_tile_center - position_);
            float dist_to_cell = to_cell.length();
            float max_move = speed_ * remaining_time;
            const float move_dist = std::min(dist_to_cell, max_move);
            const math::Vector2 displacement = current_direction_ * move_dist;

            // 3. Create a temporary hitbox
            std::shared_ptr<collision::HitBox> hit_boxe = get_hitboxe()->clone();
            hit_boxe->move_to(position_ + displacement.to_Point2());

            // 4. Checking for collisions
            if (collision_control->collision_world(hit_boxe)) {
                break;
            }

            // 5 Update position
            position_ += displacement.to_Point2();

            // 6 Update the hitbox position
            hitbox_->move_to(position_);

            // 7. If have reached the center of the cell and there is a new direction
            const bool at_cell = std::abs(move_dist - dist_to_cell) < 1e-6f;
            const bool reached_exact = (next_tile_center.x - position_.x) < 1e-4f && (next_tile_center.y - position_.y) < 1e-4f;
            const bool need_turn = at_cell ? reached_exact : next_direction_.has_same_direction(current_direction_);

            if (need_turn) {
                if (next_direction_.length() != 1.0f) next_direction_.normalize();
                current_direction_ = next_direction_;
                if (at_cell) position_ = next_tile_center;
            }

            // 8. Subtract the time used
            remaining_time -= move_dist / speed_;
        }
    }

    void Actor::act(float deltaTime, const std::shared_ptr<collision::World_Collision_Manager> &collision_control) {
        move(deltaTime, collision_control);
    }
}
