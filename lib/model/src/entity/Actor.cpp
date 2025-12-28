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
        float remaining_time = deltaTime;

        while (remaining_time > 0.0f) {

            const auto nt = grid->get_next_TilePos(position_, current_direction_);
            if (!nt.has_value()) return;
            const auto nc = grid->get_center(nt.value());
            if (!nc.has_value()) return;
            infra::math::Point2 next_center = nc.value();

            auto to_cell = infra::math::Vector2(next_center - position_);
            infra::math::Vector2 direction = to_cell.normalized();
            float dist_to_cell = to_cell.length(); // The distance that must be traveled to reach the center of the cell.
            float max_move = speed_ * remaining_time; // This is how far could go in this tick.
            const float move_dist = std::min(dist_to_cell, max_move);
            const infra::math::Vector2 displacement = direction * move_dist;

            infra::math::Vector2 allowed_move = displacement;
            auto mtv_opt = collision_control.collision_mtv_world(*hitbox_, displacement);
            if (mtv_opt.has_value()) {
                if (mtv_opt->length() < displacement.length()) {
                    allowed_move = mtv_opt.value();
                }
            }

            position_ += allowed_move.to_Point2();
            hitbox_->move_to(position_);

            // 7. If have reached the center of the cell and there is a new direction

            change_direction(grid);

            remaining_time -= allowed_move.length() / speed_;
        }
    }

    void Actor::act(float deltaTime, const collision::World_Collision_Manager &collision_control) {
        move(deltaTime, collision_control);
    }


    void Actor::change_direction(const std::shared_ptr<Tile_Grid> &grid) {
        const auto ct = grid->get_nearest_TilePos(position_);
        if (!ct.has_value()) return;
        const auto cc = grid->get_center(ct.value());
        if (!ct.has_value()) return;
        infra::math::Point2 current_center = cc.value();
        if (
            std::abs(current_center.x - position_.x) < 1e-4f &&
            std::abs(current_center.y - position_.y) < 1e-4f &&
            current_direction_ != next_direction_
        ) {
            current_direction_ = next_direction_;
            position_ = current_center;
        }
    }
}
