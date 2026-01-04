/***************************************************************
 * Project:       Pacman
 * File:          Separating_Axis_Theorem.h
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
#ifndef PACMAN_SEPARATING_AXIS_THEOREM_H
#define PACMAN_SEPARATING_AXIS_THEOREM_H

#include <memory>

#include "model/collision/collision_Control.h"

namespace model::collision {

    /**
     * @brief Collision detection using the Separating Axis Theorem (SAT).
     *
     * Implements Collision_Control to check for collisions between hitboxes
     * and calculate the Minimum Translation Vector (MTV) if a collision occurs.
     */
    class Separating_Axis_Theorem : public Collision_Control {
        public:
        /**
         * @brief Constructs the SAT collision detector.
         */
        Separating_Axis_Theorem();

        /**
         * @brief Checks if two hitboxes collide using the SAT algorithm.
         *
         * @param first First hitbox
         * @param second Second hitbox
         * @return True if collision occurs
         */
        [[nodiscard]] bool collision(const HitBox& first, const HitBox& second) const override;

        /**
         * @brief Computes the Minimum Translation Vector (MTV) to resolve collision.
         *
         * @param first First hitbox
         * @param second Second hitbox
         * @return Optional MTV vector; std::nullopt if no collision
         */
        [[nodiscard]] std::optional<infra::math::Vector2> collision_mtv(const HitBox& first, const HitBox& second) const override;
    };
}

#endif //PACMAN_SEPARATING_AXIS_THEOREM_H