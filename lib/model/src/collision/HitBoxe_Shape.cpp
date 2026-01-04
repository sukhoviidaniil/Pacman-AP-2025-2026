/***************************************************************
 * Project:       Pacman
 * File:          HitBox_Shape.cpp
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

#include <float.h>

#include "model/collision/HitBox_Shape.h"

#include <limits>
#include <stdexcept>

namespace model::collision {

    HitBox_Shape::HitBox_Shape(
        const std::vector<infra::math::Point2> &points, const int& strength):
    HitBox(strength), points_(points){
    }

    HitBox_Shape::HitBox_Shape(
        const infra::math::Point2 &pos, const float& height, const float& width, const int& strength):
    HitBox(strength){
        const float hw = width  * 0.5f;
        const float hh = height * 0.5f;

        points_.reserve(4);
        points_.emplace_back(pos.x - hw, pos.y - hh); // bottom-left
        points_.emplace_back(pos.x + hw, pos.y - hh); // bottom-right
        points_.emplace_back(pos.x + hw, pos.y + hh); // top-right
        points_.emplace_back(pos.x - hw, pos.y + hh); // top-left

        move_to(pos);
    }

    HitBox_Shape::HitBox_Shape(const HitBox_Shape &other) = default;

    HitBox_Shape::~HitBox_Shape() = default;

    std::unique_ptr<HitBox> HitBox_Shape::clone() const {
        return std::make_unique<HitBox_Shape>(*this);
    }

    std::vector<infra::math::Vector2> HitBox_Shape::get_normals() const {
        std::vector<infra::math::Vector2> normals;
        for (size_t first = 0; first < points_.size(); ++first) {
            const size_t second = (first + 1) % points_.size();
            const infra::math::Point2 d = points_[second] - points_[first];
            infra::math::Vector2 normal = {d.y, -d.x};
            // skip normalization ->
            //normal.normalize();
            normals.push_back(normal);
        }
        return normals;
    }


    AABB HitBox_Shape::get_aabb() const {
        AABB aabb;
        aabb.center = get_centers().front();
        float max_X = FLT_MIN,
        max_Y = FLT_MIN,
        min_X = FLT_MAX,
        min_Y = FLT_MAX;
        for (const infra::math::Point2 &point : points_) {
            if (max_X < point.x) {
                max_X = point.x;
            }
            if (max_Y < point.y) {
                max_Y = point.y;
            }
            if (min_X > point.x) {
               min_X = point.x;
            }
            if (min_Y > point.y) {
                min_Y = point.y;
            }
        }
        aabb.extend = {max_X, max_Y};
        return aabb;
    }

    void HitBox_Shape::move_to(const infra::math::Point2 &newPos) {
        const std::vector<infra::math::Point2> center = get_centers();
        const infra::math::Point2 delta = newPos - center.front();
        for (auto& p : points_) {
            p += delta;
        }
    }

    std::vector<float> HitBox_Shape::project(const infra::math::Vector2 &axis) const {
        float first = std::numeric_limits<float>::max();
        float second = -std::numeric_limits<float>::max();
        for (const auto& point : points_) {
            const float a = infra::math::Vector2(point).dot(axis);
            first  = std::min(first,  a);
            second = std::max(second, a);
        }
        return {first, second};
    }

    std::vector<infra::math::Point2> HitBox_Shape::get_centers() const {
        const size_t n = points_.size();
        if (n == 0) return {{0,0}};

        float area = 0.0f;
        float cx = 0.0f, cy = 0.0f;

        for (size_t i = 0; i < n; ++i) {
            const auto& current = infra::math::Vector2(points_[i]);
            const auto& next    = infra::math::Vector2(points_[(i+1) % n]);
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
