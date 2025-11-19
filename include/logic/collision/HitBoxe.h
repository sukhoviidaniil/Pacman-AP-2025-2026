/***************************************************************
 * Project:       Pacman
 * File:          HitBoxe.h
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
#include <vector>

#include "AABB.h"
#include "math/Vector2.h"

namespace Logic::Collision {
    class HitBoxe {
        unsigned int layer_ = 0;
        unsigned int strength_ = 0;
    public:
        explicit HitBoxe(unsigned int layer = 0, unsigned int strength = 0);
        virtual ~HitBoxe() = default;

        [[nodiscard]] unsigned int get_layer() const;
        [[nodiscard]] unsigned int get_strength() const;

        [[nodiscard]] virtual std::vector<Math::Vector2> get_normals() const = 0;

        /**
         *
         * @param hit_boxe
         * @return All vectors that will go from the center of this hitbox to the center of another
         */
        [[nodiscard]] virtual std::vector<Math::Vector2> get_vector_to(const HitBoxe &hit_boxe) const;

        [[nodiscard]] virtual AABB get_aabb() const = 0;

        virtual void move_to(const Math::Vector2& newPos) = 0;

        /** Each pair in the vector is a separate sub-hitbox.
         *
         *
         * @param axis The axis onto which the projection will be made; It can be normalized and ONLY NORMALIZED; no change in direction is allowed.
         * @return Vector of all projections onto the axis
         */
        [[nodiscard]] virtual std::vector<float> project(const Math::Vector2 &axis) const = 0;

        /**
         *
         * @return All centers of all sub-hitboxes, including the common one
         */
        [[nodiscard]] virtual std::vector<Math::Vector2> get_centers() const = 0;
    };
}

#endif //PACMAN_HITBOXE_H
