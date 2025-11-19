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

#include "logic/collision/HitBoxe_Shape.h"

#include <limits>
#include <stdexcept>

namespace Logic::Collision {

    HitBoxe_Shape::HitBoxe_Shape(const std::vector<Math::Vector2> &points, const unsigned int layer, const unsigned int strength):
    HitBoxe(layer, strength), points_(points){
    }

    HitBoxe_Shape::HitBoxe_Shape(const Math::Vector2 &pos, const float height, const float width, unsigned int layer, unsigned int strength):
    HitBoxe(layer, strength){


        const float hw = width  * 0.5f;
        const float hh = height * 0.5f;

        points_.reserve(4);
        points_.push_back({pos.x - hw, pos.y - hh}); // bottom-left
        points_.push_back({pos.x + hw, pos.y - hh}); // bottom-right
        points_.push_back({pos.x + hw, pos.y + hh}); // top-right
        points_.push_back({pos.x - hw, pos.y + hh}); // top-left

        move_to(pos);
    }

    HitBoxe_Shape::~HitBoxe_Shape() = default;

    std::vector<Math::Vector2> HitBoxe_Shape::get_normals() const {
        std::vector<Math::Vector2> normals;
        for (size_t first = 0; first < points_.size(); ++first) {
            const size_t second = (first + 1) % points_.size();
            const Math::Vector2 d = points_[second] - points_[first];
            Math::Vector2 normal = {d.y, -d.x};
            // skip normalization ->
            //normal.normalize();
            normals.push_back(normal);
        }
        return normals;
    }

    std::vector<Math::Vector2> HitBoxe_Shape::get_vector_to(const HitBoxe &hit_boxe) const {
        std::vector<Math::Vector2> m_centers = get_centers();
        std::vector<Math::Vector2> f_centers = hit_boxe.get_centers();
        std::vector<Math::Vector2> all_centers;
        for (const auto& f_center : f_centers) {
            for (const auto& m_center : m_centers) {
                Math::Vector2 dir = f_center - m_center;
                all_centers.push_back(dir);
            }
        }
        return all_centers;
    }

    AABB HitBoxe_Shape::get_aabb() const {
        AABB aabb;
        for (const Math::Vector2 &point : points_) {
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
        return aabb;
    }

    void HitBoxe_Shape::move_to(const Math::Vector2 &newPos) {
        const std::vector<Math::Vector2> center = get_centers();
        const Math::Vector2 delta = newPos - center.front();
        for (auto& p : points_) {
            p += delta;
        }
    }

    std::vector<float> HitBoxe_Shape::project(const Math::Vector2 &axis) const {
        float first = std::numeric_limits<float>::max();
        float second = -std::numeric_limits<float>::max();
        for (const auto& point : points_) {
            const float a = point.dot(axis);
            first  = std::min(first,  a);
            second = std::max(second, a);
        }
        return {first, second};
    }

    std::vector<Math::Vector2> HitBoxe_Shape::get_centers() const {
        const size_t n = points_.size();
        if (n == 0) return {{0,0}};

        float area = 0.0f;
        float cx = 0.0f, cy = 0.0f;

        for (size_t i = 0; i < n; ++i) {
            const Math::Vector2& current = points_[i];
            const Math::Vector2& next    = points_[(i+1) % n];
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
