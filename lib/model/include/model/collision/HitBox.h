/***************************************************************
 * Project:       Pacman
 * File:          HitBox.h
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
#ifndef PACMAN_HITBOXE_H
#define PACMAN_HITBOXE_H

#include "infra/math/Vector2.h"
#include "model/collision/AABB.h"
#include <vector>
#include <memory>

namespace model::collision {
    class HitBox {
    public:
        explicit HitBox(int strength);
        HitBox(const HitBox &other);
        virtual ~HitBox();

        [[nodiscard]] int get_strength() const;

        [[nodiscard]] virtual std::unique_ptr<HitBox> clone() const = 0;

        [[nodiscard]] virtual AABB get_aabb() const = 0;

        [[nodiscard]] virtual std::vector<infra::math::Vector2> get_normals() const = 0;

        /**
         *
         * @param hit_boxe
         * @return All vectors that will go from the center of this hitbox to the center of another
         */
        [[nodiscard]] virtual std::vector<infra::math::Vector2> get_vector_to(const HitBox& hit_boxe) const;


        virtual void move_to(const infra::math::Point2& newPos) = 0;

        /** Each pair in the vector is a separate sub-hitbox.
         *
         *
         * @param axis The axis onto which the projection will be made; It can be normalized and ONLY NORMALIZED; no change in direction is allowed.
         * @return Vector of all projections onto the axis
         */
        [[nodiscard]] virtual std::vector<float> project(const infra::math::Vector2 &axis) const = 0;

        /**
         *
         * @return All centers of all sub-hitboxes, including the common one
         */
        [[nodiscard]] virtual std::vector<infra::math::Point2> get_centers() const = 0;
    private:
        int strength_ = 0;
    };
}

#endif //PACMAN_HITBOXE_H
