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

#include <iostream>

#include "infra/diagnostics/Logger.h"

namespace model::entity{
    Actor::~Actor() = default;

    Actor::Actor(
        const std::string &name, const float size, const infra::math::Point2 &position,
        std::unique_ptr<collision::HitBox> hitbox, const infra::math::Direction &current_direction, float speed
        )
        : Entity(name, size, position, std::move(hitbox)), current_direction_(current_direction), speed_(speed){
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
        const collision::World_Collision_Manager &collision_control
        ) {

        if (speed_ <= 0.f) return;
        const auto grid = collision_control.get_grid();
        float remaining_dist = speed_ * deltaTime;
        const float EPS = grid->tile_size() * 0.001f;


        while (remaining_dist > EPS) {
            // 1. Current cell
            auto cur_tilepos = grid->get_TilePos(position());
            if (!cur_tilepos.has_value()) {
                break;
            }
            infra::math::Point2 center = grid->get_center(cur_tilepos.value());

            // vector and distance to center
            infra::math::Vector2 to_center = infra::math::Vector2(center - position_);
            float dist_to_center = to_center.length();


            // SNAP to center if almost in it
            if (dist_to_center <= EPS) {
                position_ = center;
                hitbox_->move_to(position_);
                dist_to_center = 0.0f;
            }

            // Attempt to move toward the center
            if (dist_to_center > EPS) {
                const infra::math::Vector2 move_dir = infra::math::to_vec(current_direction_);
                if (to_center.dot(move_dir) > 0.0f) {

                    const float step = std::min(dist_to_center, remaining_dist);
                    const infra::math::Vector2 dir = to_center / dist_to_center;
                    position_ += (dir * step).to_Point2();
                    remaining_dist -= step;

                    // if we haven't reached the center, we update the hitbox and continue the cycle
                    if (step < dist_to_center) {
                        hitbox_->move_to(position_);
                        continue;
                    }

                    // reached exactly the center
                    position_ = center;
                    dist_to_center = 0;
                }
            }

            const infra::math::Point2 src_for_next = dist_to_center == 0.0f ? center : position_;

            // 3. In the center — you can change the direction
            if (current_direction_ != next_direction_) {
                if (const auto cand = grid->get_next_TilePos(src_for_next, next_direction_)) {
                    const Tile cand_tile = grid->get_tile(*cand);
                    if (walkable(cand_tile)) {
                        current_direction_ = next_direction_;
                        position_ = center; // when changing direction, the position is centered
                        hitbox_->move_to(position_);
                    }
                }
            }

            //
            const auto next_tilepos = grid->get_next_TilePos(position_, current_direction_);
            if (!next_tilepos) break;
            const infra::math::Point2 next_center = grid->get_center(*next_tilepos);
            const Tile next_tile = grid->get_tile(*next_tilepos);

            // If the next tile is impassable, stay in the center of the current tile and exit.
            if (!walkable(next_tile)) {
                position_ = center;
                hitbox_->move_to(position_);
                break;
            }

            // Move to the center of the next cell (including partial movement)
            const infra::math::Vector2 to_next(next_center - position_);
            const float dist_next = to_next.length();
            if (dist_next <= EPS) {
                // in case of numerical errors — jump to the center of the next one
                position_ = next_center;
                hitbox_->move_to(position_);
                continue;
            }

            const float step_next = std::min(dist_next, remaining_dist);
            const infra::math::Vector2 dir_next = to_next / dist_next;
            position_ += (dir_next * step_next).to_Point2();
            remaining_dist -= step_next;
        }
    }

    void Actor::act(float deltaTime, const collision::World_Collision_Manager &collision_control) {
        move(deltaTime, collision_control);
    }

}
