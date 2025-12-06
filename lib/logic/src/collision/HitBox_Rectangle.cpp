/***************************************************************
 * Project:       Pacman
 * File:          HitBox_Rectangle.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-06
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

#include "logic/collision/HitBox_Rectangle.h"

namespace Logic::Collision {
    HitBox_Rectangle::HitBox_Rectangle(
        const Math::Vector2 &center, const float width, const float height
        ):
        center_(center), width_(width), height_(height)
    {
    }

    HitBox_Rectangle::HitBox_Rectangle(
        const Math::Vector2 &center, const float width, const float height, const unsigned int layer, const unsigned int strength
        ):
        HitBoxe(layer, strength), center_(center), width_(width), height_(height)
    {
    }

    HitBox_Rectangle::HitBox_Rectangle(const HitBox_Rectangle &other)  : HitBoxe(other) {
        center_ = other.center_;
        width_ = other.width_;
        height_ = other.height_;
    }

    std::shared_ptr<HitBoxe> HitBox_Rectangle::clone() const {
        return std::make_shared<HitBox_Rectangle>(*this);
    }

    std::vector<Math::Vector2> HitBox_Rectangle::get_vector_to(const std::shared_ptr<HitBoxe> &hit_boxe) const {
        return HitBoxe::get_vector_to(hit_boxe);
    }

    std::vector<Math::Vector2> HitBox_Rectangle::get_normals() const {
        return {Math::Vector2(1,0), Math::Vector2(0,1)};
    }

    AABB HitBox_Rectangle::get_aabb() const {
        AABB aabb;
        aabb.center = center_;
        aabb.extend = Math::Vector2(width_, height_);
        return aabb;
    }

    void HitBox_Rectangle::move_to(const Math::Vector2 &newPos) {
        center_ = newPos;
    }

    std::vector<float> HitBox_Rectangle::project(const Math::Vector2 &axis) const {
        float half_w = width_ / 2.0f;
        float half_h = height_ / 2.0f;

        std::vector<Math::Vector2> corners = {
            {center_.x - half_w, center_.y - half_h},
            {center_.x + half_w, center_.y - half_h},
            {center_.x + half_w, center_.y + half_h},
            {center_.x - half_w, center_.y + half_h}
        };

        // Project each vertex onto the axis
        float min_proj = corners[0].dot(axis);
        float max_proj = min_proj;

        for (size_t i = 1; i < corners.size(); ++i) {
            float proj = corners[i].dot(axis);
            if (proj < min_proj) min_proj = proj;
            if (proj > max_proj) max_proj = proj;
        }

        return {min_proj, max_proj};
    }

    std::vector<Math::Vector2> HitBox_Rectangle::get_centers() const {
        return {center_};
    }
}
