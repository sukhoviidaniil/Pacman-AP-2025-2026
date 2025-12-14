/***************************************************************
 * Project:       Pacman
 * File:          HitBoxe_Shape.cpp
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

#include "model/collision/HitBoxe_Shape.h"

#include <limits>
#include <stdexcept>

namespace model::collision {

    HitBoxe_Shape::HitBoxe_Shape(
        const std::vector<math::Point2> &points, const int& strength):
    HitBoxe(strength), points_(points){
    }

    HitBoxe_Shape::HitBoxe_Shape(
        const math::Point2 &pos, const float& height, const float& width, const int& strength):
    HitBoxe(strength){
        const float hw = width  * 0.5f;
        const float hh = height * 0.5f;

        points_.reserve(4);
        points_.emplace_back(pos.x - hw, pos.y - hh); // bottom-left
        points_.emplace_back(pos.x + hw, pos.y - hh); // bottom-right
        points_.emplace_back(pos.x + hw, pos.y + hh); // top-right
        points_.emplace_back(pos.x - hw, pos.y + hh); // top-left

        move_to(pos);
    }

    HitBoxe_Shape::HitBoxe_Shape(const HitBoxe_Shape &other) = default;

    HitBoxe_Shape::~HitBoxe_Shape() = default;

    std::shared_ptr<HitBoxe> HitBoxe_Shape::clone() const {
        return std::make_shared<HitBoxe_Shape>(*this);
    }

    std::vector<math::Vector2> HitBoxe_Shape::get_normals() const {
        std::vector<math::Vector2> normals;
        for (size_t first = 0; first < points_.size(); ++first) {
            const size_t second = (first + 1) % points_.size();
            const math::Point2 d = points_[second] - points_[first];
            math::Vector2 normal = {d.y, -d.x};
            // skip normalization ->
            //normal.normalize();
            normals.push_back(normal);
        }
        return normals;
    }


    AABB HitBoxe_Shape::get_aabb() const {
        AABB aabb;
        aabb.center = get_centers().front();
        for (const math::Point2 &point : points_) {
            if (aabb.max_X < point.x) {
                aabb.max_X = point.x;
            }
            if (aabb.max_Y < point.y) {
                aabb.max_Y = point.y;
            }
            if (aabb.min_X > point.x) {
                aabb.min_X = point.x;
            }
            if (aabb.min_Y > point.y) {
                aabb.min_Y = point.y;
            }
        }
        aabb.extend = {aabb.max_X, aabb.max_Y};
        return aabb;
    }

    void HitBoxe_Shape::move_to(const math::Point2 &newPos) {
        const std::vector<math::Point2> center = get_centers();
        const math::Point2 delta = newPos - center.front();
        for (auto& p : points_) {
            p += delta;
        }
    }

    std::vector<float> HitBoxe_Shape::project(const math::Vector2 &axis) const {
        float first = std::numeric_limits<float>::max();
        float second = -std::numeric_limits<float>::max();
        for (const auto& point : points_) {
            const float a = math::Vector2(point).dot(axis);
            first  = std::min(first,  a);
            second = std::max(second, a);
        }
        return {first, second};
    }

    std::vector<math::Point2> HitBoxe_Shape::get_centers() const {
        const size_t n = points_.size();
        if (n == 0) return {{0,0}};

        float area = 0.0f;
        float cx = 0.0f, cy = 0.0f;

        for (size_t i = 0; i < n; ++i) {
            const auto& current = math::Vector2(points_[i]);
            const auto& next    = math::Vector2(points_[(i+1) % n]);
            const float cross = current.cross(next);
            area += cross;
            cx += (current.x + next.x) * cross;
            cy += (current.y + next.y) * cross;
        }

        area *= 0.5f;
        if (area == 0.0f) {
            // degenerate polygon
            return {{0,0}};
        }

        cx /= 6.0f * area;
        cy /= 6.0f * area;

        return {{cx, cy}};
    }
}
