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

#include "model/entity/Entity.h"

namespace model {

    Entity::Entity(
        std::string name, float size, const infra::math::Point2 &position, std::unique_ptr<collision::HitBox> hitbox
        ):
        position_(position), hitbox_(std::move(hitbox)), size_(size), name_(std::move(name))
    {
        hitbox_->move_to(position_);
    }

    Entity::~Entity() = default;

    std::string Entity::name() const {
        return name_;
    }

    float Entity::size() const {
        return size_;
    }

    infra::math::Point2 Entity::position() const {
        return position_;
    }

    const collision::HitBox& Entity::hitboxe() const {
        return *hitbox_;
    }

    infra::ui::Rect Entity::rect() const {
        collision::AABB aabb = hitboxe().get_aabb();
        return {aabb.center.x, aabb.center.y, aabb.extend.x, aabb.extend.y};
    }
}
