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

#include "model/collision/HitBox.h"

namespace model::collision {
    class HitBox_Rectangle : public HitBox {
        public:
        HitBox_Rectangle(float width, float height, int strength);
        HitBox_Rectangle(const infra::math::Point2& center, float width, float height, int strength);

        HitBox_Rectangle(const HitBox_Rectangle& other);

        [[nodiscard]] std::unique_ptr<HitBox> clone() const override;

        [[nodiscard]] std::vector<infra::math::Vector2> get_normals() const override;

        [[nodiscard]] AABB get_aabb() const override;

        void move_to(const  infra::math::Point2& newPos) override;

        [[nodiscard]] std::vector<float> project(const infra::math::Vector2 &axis) const override;

        [[nodiscard]] std::vector<infra::math::Point2> get_centers() const override;

    private:
        infra::math::Point2 center_ = {0,0};
        float width_;
        float height_;
    };
}

#endif //PACMAN_HITBOX_RECTANGLE_H