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

#include "logic/model/Entity.h"

namespace Logic::Model {

    Entity::Entity(
        std::string name,
        const Math::Vector2 &position,
        const std::shared_ptr<Collision::HitBoxe>& hitbox,
        const unsigned int status):
        name_(std::move(name)), position_(position), hitbox_(hitbox), status_(status){

        hitbox_->move_to(position);
    }

    Entity::Entity(const Math::Vector2 &vector2): position_(vector2) {
    }

    Entity::~Entity() = default;

    std::string Entity::get_name() const {
        return name_;
    }

    Math::Vector2 Entity::get_position() const {
        return position_;
    }

    std::shared_ptr<Collision::HitBoxe> Entity::get_hitboxe() {
        return hitbox_;
    }

    unsigned int Entity::get_status() const {
        return status_;
    }

}
