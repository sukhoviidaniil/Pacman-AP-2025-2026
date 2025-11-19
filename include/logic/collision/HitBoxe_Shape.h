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

#include "HitBoxe.h"
#include "math/Vector2.h"

namespace Logic::Collision {
    class HitBoxe_Shape final : public HitBoxe {
        std::vector<Math::Vector2> points_;
        public:
        explicit HitBoxe_Shape(const std::vector<Math::Vector2> &points, unsigned int layer = 0, unsigned int strength = 0);

        explicit HitBoxe_Shape(const Math::Vector2 &pos, float height, float width, unsigned int layer = 0, unsigned int strength = 0);
        ~HitBoxe_Shape() override;

        [[nodiscard]] std::vector<Math::Vector2> get_normals() const override;

        [[nodiscard]] std::vector<Math::Vector2> get_vector_to(const HitBoxe &hit_boxe) const override;

        [[nodiscard]] AABB get_aabb() const override;

        void move_to(const Math::Vector2& newPos) override;

        [[nodiscard]] std::vector<float> project(const Math::Vector2 &axis) const override;

        [[nodiscard]] std::vector<Math::Vector2> get_centers() const override;
    };
}

#endif //PACMAN_HITBOXE_SHAPE_H