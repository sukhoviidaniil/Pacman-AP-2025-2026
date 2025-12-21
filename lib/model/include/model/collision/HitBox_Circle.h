/***************************************************************
 * Project:       Pacman
 * File:          HitBox_Circle.h
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

#include "model/collision/HitBox.h"

namespace model::collision {
    class HitBox_Circle final : public HitBox {

    public:
        explicit HitBox_Circle(const int& strength, const infra::math::Point2 &center, const float& radius);
        HitBox_Circle(const HitBox_Circle & other);
        ~HitBox_Circle() override;

        void move_to(const infra::math::Point2 &pos) override;
        [[nodiscard]] std::unique_ptr<HitBox> clone() const override;
        [[nodiscard]] AABB get_aabb() const override;
        [[nodiscard]] std::vector<infra::math::Vector2> get_normals() const override;
        [[nodiscard]] std::vector<infra::math::Vector2> get_vector_to(const HitBox &hit_boxe) const override;
        [[nodiscard]] std::vector<float> project(const infra::math::Vector2 &axis) const override;
        [[nodiscard]] std::vector<infra::math::Point2> get_centers() const override;
    private:
        infra::math::Point2 center_;
        float radius_;
    };
}

#endif //PACMAN_HITBOXE_CIRCLE_H