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

#include <cmath>
#include "infra/math/to_Vector2.h"
#include "model/entity/Actor.h"

namespace model::entity{
    Actor::~Actor() = default;

    Actor::Actor(
        const std::string &name, const infra::math::Point2 &position,
        std::unique_ptr<collision::HitBox> hitbox, const infra::math::Direction &current_direction, float speed
        )
        : Entity(name, position, std::move(hitbox)), current_direction_(current_direction), speed_(speed){
        next_direction_ = current_direction_;
    }


    infra::math::Direction Actor::get_direction() const {
        return current_direction_;
    }

    void Actor::set_direction(const infra::math::Direction &direction) {
        next_direction_ = direction;
    }

    void Actor::to_left() {
        set_direction(infra::math::Direction::Left);
    }

    void Actor::to_right() {
        set_direction(infra::math::Direction::Right);
    }

    void Actor::to_up() {
        set_direction(infra::math::Direction::Up);
    }

    void Actor::to_down() {
        set_direction(infra::math::Direction::Down);
    }

    void Actor::move(
        const float deltaTime,
        const std::shared_ptr<collision::World_Collision_Manager> &collision_control
        ) {

        const std::shared_ptr<const Tile_Grid> grid = collision_control->get_grid();

        if (speed_ == 0.0f) return;

        float remaining_time = deltaTime;

        while (remaining_time > 0.0f) {
            infra::math::Vector2 direction = to_vec(current_direction_);
            // 1. Calculate the next tile coordinate on the path current_dir
            std::shared_ptr<const Tile> t = grid->get_next_tile(position_, direction);
            if (t == nullptr) {
                throw std::invalid_argument("Not a valid tile for Actor - Actor out bounds;");
            }
            const infra::math::Point2& next_tile_center = t->get_position();

            // 2. Calculate the maximum possible displacement to this coordinate
            auto to_cell = infra::math::Vector2(next_tile_center - position_);
            float dist_to_cell = to_cell.length();
            float max_move = speed_ * remaining_time;
            const float move_dist = std::min(dist_to_cell, max_move);
            const infra::math::Vector2 displacement = direction * move_dist;

            // 3. Move HitBox
            hitbox_->move_to(position_ + displacement.to_Point2());

            // 4. Checking for collisions
            if (collision_control->collision_world(*hitbox_)) {
                // Abort move
                hitbox_->move_to(position_ );
                break;
            }

            // 5 Update position
            position_ += displacement.to_Point2();

            infra::math::Vector2 n_direction = to_vec(next_direction_);

            // 7. If have reached the center of the cell and there is a new direction
            const bool at_cell = std::abs(move_dist - dist_to_cell) < 1e-6f;
            const bool reached_exact = (next_tile_center.x - position_.x) < 1e-4f && (next_tile_center.y - position_.y) < 1e-4f;
            const bool need_turn = at_cell ? reached_exact : n_direction.has_same_direction(direction);

            if (need_turn) {
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
