/***************************************************************
 * Project:       Pacman
 * File:          HitBoxe_Circle.cpp
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

#include "model/collision/HitBoxe_Circle.h"

namespace model::collision {
    HitBoxe_Circle::HitBoxe_Circle(const HitBoxe_Circle &other) = default;

    HitBoxe_Circle::HitBoxe_Circle(
        const int& strength, const math::Point2 &center, const float& radius
        ):
        HitBoxe(strength), center_(center), radius_(radius) {
    }

    HitBoxe_Circle::~HitBoxe_Circle() = default;

    std::vector<math::Vector2> HitBoxe_Circle::get_vector_to(const std::shared_ptr<const HitBoxe> &hit_boxe) const {
        return HitBoxe::get_vector_to(hit_boxe);
    }

    void HitBoxe_Circle::move_to(const math::Point2 &pos) {
        center_ = pos;
    }

    std::shared_ptr<HitBoxe> HitBoxe_Circle::clone() const {
        return std::make_shared<HitBoxe_Circle>(*this);
    }

    AABB HitBoxe_Circle::get_aabb() const {
        AABB aabb;
        aabb.center = center_;
        aabb.extend = {radius_, radius_};
        aabb.max_X = center_.x + radius_;
        aabb.min_X = center_.x - radius_;
        aabb.max_Y = center_.y + radius_;
        aabb.min_Y = center_.y - radius_;
        return aabb;
    }

    std::vector<math::Vector2> HitBoxe_Circle::get_normals() const {
        return {{0,1}, {1,0}};
    }


    std::vector<float> HitBoxe_Circle::project(const math::Vector2 &axis) const {
        std::vector<float> points;
        const float p_center = math::Vector2(center_) .dot(axis);
        points.push_back(p_center - radius_);
        points.push_back(p_center + radius_);
        return points;
    }

    std::vector<math::Point2> HitBoxe_Circle::get_centers() const {
        return {center_};
    }
}
