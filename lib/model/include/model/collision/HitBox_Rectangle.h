/***************************************************************
 * Project:       Pacman
 * File:          HitBox_Rectangle.h
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
#ifndef PACMAN_HITBOX_RECTANGLE_H
#define PACMAN_HITBOX_RECTANGLE_H

#include "model/collision/HitBoxe.h"

namespace model::collision {
    class HitBox_Rectangle : public HitBoxe {
        public:
        HitBox_Rectangle(float width, float height, int strength);
        HitBox_Rectangle(const math::Point2& center, float width, float height, int strength);

        HitBox_Rectangle(const HitBox_Rectangle& other);

        [[nodiscard]] std::shared_ptr<HitBoxe> clone() const override;

        [[nodiscard]] std::vector<math::Vector2> get_vector_to(const std::shared_ptr<const HitBoxe> &hit_boxe) const override;

        [[nodiscard]] std::vector<math::Vector2> get_normals() const override;

        [[nodiscard]] AABB get_aabb() const override;

        void move_to(const  math::Point2& newPos) override;

        [[nodiscard]] std::vector<float> project(const math::Vector2 &axis) const override;

        [[nodiscard]] std::vector<math::Point2> get_centers() const override;

    private:
        math::Point2 center_;
        float width_;
        float height_;
    };
}

#endif //PACMAN_HITBOX_RECTANGLE_H