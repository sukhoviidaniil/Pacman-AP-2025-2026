/***************************************************************
 * Project:       Pacman
 * File:          Entity.cpp
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

#include <utility>

#include "model/Entity.h"

namespace model {

    Entity::Entity(
        std::string name, const math::Point2 &position, const std::shared_ptr<collision::HitBoxe> &hitbox
        ):
        position_(position), hitbox_(hitbox), name_(std::move(name))
    {
        hitbox_->move_to(position_);
    }

    Entity::~Entity() = default;

    std::string Entity::get_name() const {
        return name_;
    }

    math::Point2 Entity::get_position() const {
        return position_;
    }

    std::shared_ptr<const collision::HitBoxe> Entity::get_hitboxe() {
        return hitbox_;
    }
}
