/***************************************************************
 * Project:       Pacman
 * File:          HitBoxe_Circle.h
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
#ifndef PACMAN_HITBOXE_CIRCLE_H
#define PACMAN_HITBOXE_CIRCLE_H
#include "HitBoxe.h"

namespace Logic::Collision {
    class HitBoxe_Circle final : public HitBoxe {
        Math::Vector2 center_;
        float radius_;
    public:
        explicit HitBoxe_Circle(unsigned int layer = 0, unsigned int strength = 0, const Math::Vector2 &center = {0,0}, float radius = 1);
        ~HitBoxe_Circle() override;
        [[nodiscard]] std::vector<Math::Vector2> get_normals() const override;
        [[nodiscard]] std::vector<Math::Vector2> get_vector_to(const HitBoxe &hit_boxe) const override;
        [[nodiscard]] std::vector<float> project(const Math::Vector2 &axis) const override;
        [[nodiscard]] std::vector<Math::Vector2> get_centers() const override;
    };
}

#endif //PACMAN_HITBOXE_CIRCLE_H