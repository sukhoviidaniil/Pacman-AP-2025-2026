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

#include "logic/collision/HitBoxe_Circle.h"

namespace Logic::Collision {
    HitBoxe_Circle::HitBoxe_Circle(const unsigned int layer, const unsigned int strength, const Math::Vector2 &center, const float radius):
    HitBoxe(layer, strength), center_(center), radius_(radius) {
    }

    HitBoxe_Circle::~HitBoxe_Circle() = default;

    std::vector<Math::Vector2> HitBoxe_Circle::get_normals() const {
        return {{0,1}, {1,0}};
    }

    std::vector<Math::Vector2> HitBoxe_Circle::get_vector_to(const HitBoxe &hit_boxe) const {
        return {{0,1}, {1,0}};
    }

    std::vector<float> HitBoxe_Circle::project(const Math::Vector2 &axis) const {
        std::vector<float> points;
        const float p_center = center_.dot(axis);
        points.push_back(p_center - radius_);
        points.push_back(p_center + radius_);
        return points;
    }

    std::vector<Math::Vector2> HitBoxe_Circle::get_centers() const {
        return {center_};
    }
}
