/***************************************************************
 * Project:       Pacman
 * File:          HitBox_Circle.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-15
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

#include "model/collision/HitBox_Circle.h"

namespace model::collision {
    HitBox_Circle::HitBox_Circle(const HitBox_Circle &other) = default;

    HitBox_Circle::HitBox_Circle(
        const int& strength, const infra::math::Point2 &center, const float& radius
        ):
        HitBox(strength), center_(center), radius_(radius) {
    }

    HitBox_Circle::~HitBox_Circle() = default;

    std::vector<infra::math::Vector2> HitBox_Circle::get_vector_to(const HitBox &hit_boxe) const {
        return HitBox::get_vector_to(hit_boxe);
    }

    void HitBox_Circle::move_to(const infra::math::Point2 &pos) {
        center_ = pos;
    }

    std::unique_ptr<HitBox> HitBox_Circle::clone() const {
        return std::make_unique<HitBox_Circle>(*this);
    }

    AABB HitBox_Circle::get_aabb() const {
        AABB aabb;
        aabb.center = center_;
        aabb.extend = {radius_, radius_};
        aabb.max_X = center_.x + radius_;
        aabb.min_X = center_.x - radius_;
        aabb.max_Y = center_.y + radius_;
        aabb.min_Y = center_.y - radius_;
        return aabb;
    }

    std::vector<infra::math::Vector2> HitBox_Circle::get_normals() const {
        return {{0,1}, {1,0}};
    }


    std::vector<float> HitBox_Circle::project(const infra::math::Vector2 &axis) const {
        std::vector<float> points;
        const float p_center = infra::math::Vector2(center_) .dot(axis);
        points.push_back(p_center - radius_);
        points.push_back(p_center + radius_);
        return points;
    }

    std::vector<infra::math::Point2> HitBox_Circle::get_centers() const {
        return {center_};
    }
}
