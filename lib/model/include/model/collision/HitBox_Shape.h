/***************************************************************
 * Project:       Pacman
 * File:          HitBox_Shape.h
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

#include "model/collision/HitBox.h"

namespace model::collision {
    class HitBox_Shape final : public HitBox {
        public:
        explicit HitBox_Shape(const std::vector<infra::math::Point2> &points, const int& strength);
        explicit HitBox_Shape(const infra::math::Point2 &pos, const float& height, const float& width, const int& strength);
        HitBox_Shape(const HitBox_Shape & other);
        ~HitBox_Shape() override;

        [[nodiscard]] std::unique_ptr<HitBox> clone() const override;

        [[nodiscard]] std::vector<infra::math::Vector2> get_normals() const override;

        [[nodiscard]] AABB get_aabb() const override;

        void move_to(const infra::math::Point2& pos) override;

        [[nodiscard]] std::vector<float> project(const infra::math::Vector2 &axis) const override;

        [[nodiscard]] std::vector<infra::math::Point2> get_centers() const override;
    private:
        std::vector<infra::math::Point2> points_;
    };
}

#endif //PACMAN_HITBOXE_SHAPE_H