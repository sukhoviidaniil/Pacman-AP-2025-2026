/***************************************************************
 * Project:       Pacman
 * File:          HitBoxe_Shape.h
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
#ifndef PACMAN_HITBOXE_SHAPE_H
#define PACMAN_HITBOXE_SHAPE_H

#include "model/collision/HitBoxe.h"

namespace model::collision {
    class HitBoxe_Shape final : public HitBoxe {
        public:
        explicit HitBoxe_Shape(const std::vector<math::Point2> &points, const int& strength);
        explicit HitBoxe_Shape(const math::Point2 &pos, const float& height, const float& width, const int& strength);
        HitBoxe_Shape(const HitBoxe_Shape & other);
        ~HitBoxe_Shape() override;

        [[nodiscard]] std::shared_ptr<HitBoxe> clone() const override;


        [[nodiscard]] std::vector<math::Vector2> get_normals() const override;

        [[nodiscard]] AABB get_aabb() const override;

        void move_to(const math::Point2& pos) override;

        [[nodiscard]] std::vector<float> project(const math::Vector2 &axis) const override;

        [[nodiscard]] std::vector<math::Point2> get_centers() const override;
    private:
        std::vector<math::Point2> points_;
    };
}

#endif //PACMAN_HITBOXE_SHAPE_H