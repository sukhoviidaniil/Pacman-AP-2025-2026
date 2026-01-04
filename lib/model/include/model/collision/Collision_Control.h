/***************************************************************
 * Project:       Pacman
 * File:          collision_Control.h
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
#ifndef PACMAN_COLLISION_CONTROL_H
#define PACMAN_COLLISION_CONTROL_H

#include "model/collision/HitBox.h"
#include <optional>

namespace model::collision {
    /**
     * @brief Interface for collision detection between hitboxes.
     *
     * Provides methods to check for collision and to calculate the
     * Minimum Translation Vector (MTV) for collision resolution.
     */
    class Collision_Control {
        public:
        /**
         * @brief Virtual destructor for proper polymorphic cleanup.
         */
        virtual ~Collision_Control() = default;

        /**
         * @brief Checks if two hitboxes are colliding.
         *
         * @param first First hitbox
         * @param second Second hitbox
         * @return True if a collision occurs
         */
        [[nodiscard]] virtual bool collision(const HitBox& first,const HitBox& second) const = 0;

        /**
         * @brief Calculates the Minimum Translation Vector (MTV) to resolve collision.
         *
         * @param first First hitbox
         * @param second Second hitbox
         * @return Optional vector representing the MTV; std::nullopt if no collision
         */
        [[nodiscard]] virtual std::optional<infra::math::Vector2> collision_mtv(const HitBox& first, const HitBox& second) const = 0;

    };
}

#endif //PACMAN_COLLISION_CONTROL_H