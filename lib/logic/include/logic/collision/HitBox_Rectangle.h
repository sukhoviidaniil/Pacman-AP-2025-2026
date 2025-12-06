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

#include "HitBoxe.h"

namespace Logic::Collision {
    class HitBox_Rectangle : public HitBoxe {

        Math::Vector2 center_;
        float width_;
        float height_;

        public:
        HitBox_Rectangle(const Math::Vector2& center, float width, float height);
        HitBox_Rectangle(const Math::Vector2& center, float width, float height, unsigned int layer, unsigned int strength);

        HitBox_Rectangle(const HitBox_Rectangle& other);

        [[nodiscard]] std::shared_ptr<HitBoxe> clone() const override;

        [[nodiscard]] std::vector<Math::Vector2> get_vector_to(const std::shared_ptr<HitBoxe> &hit_boxe) const override;

        [[nodiscard]] std::vector<Math::Vector2> get_normals() const override;

        [[nodiscard]] AABB get_aabb() const override;

        void move_to(const Math::Vector2& newPos) override;

        [[nodiscard]] std::vector<float> project(const Math::Vector2 &axis) const override;

        [[nodiscard]] std::vector<Math::Vector2> get_centers() const override;
    };
}

#endif //PACMAN_HITBOX_RECTANGLE_H