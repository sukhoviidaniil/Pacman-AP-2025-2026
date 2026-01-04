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

#include "model/collision/AABB.h"
#include <vector>
#include <memory>

namespace model::collision {
    /**
     * @brief Abstract base class representing a collision hitbox.
     *
     * Stores a strength value and provides an interface for AABB retrieval,
     * normal vectors, projections, movement, and cloning.
     */
    class HitBox {
    public:
        /**
         * @brief Constructs a HitBox with a given strength.
         *
         * @param strength Hitbox strength
         */
        explicit HitBox(int strength);

        /**
         * @brief Copy constructor.
         */
        HitBox(const HitBox &other);

        /**
         * @brief Virtual destructor for proper polymorphic cleanup.
         */
        virtual ~HitBox();

        /**
         * @brief Returns the strength of this hitbox.
         */
        [[nodiscard]] int get_strength() const;

        /**
         * @brief Creates a deep copy of the hitbox.
         *
         * @return Unique pointer to the cloned HitBox
         */
        [[nodiscard]] virtual std::unique_ptr<HitBox> clone() const = 0;

        /**
         * @brief Returns the axis-aligned bounding box for the hitbox.
         */
        [[nodiscard]] virtual AABB get_aabb() const = 0;

        /**
         * @brief Returns the normal vectors of the hitbox surfaces.
         */
        [[nodiscard]] virtual std::vector<infra::math::Vector2> get_normals() const = 0;

        /**
         * @brief Returns vectors from this hitbox's center(s) to another hitbox's center(s).
         *
         * @param hit_boxe Other hitbox
         * @return Vector of center-to-center vectors
         */
        [[nodiscard]] virtual std::vector<infra::math::Vector2> get_vector_to(const HitBox& hit_boxe) const;

        /**
         * @brief Moves the hitbox to a new position.
         *
         * @param newPos Target center position
         */
        virtual void move_to(const infra::math::Point2& newPos) = 0;

        /**
         * @brief Projects the hitbox onto a given axis.
         *
         * Each sub-hitbox contributes separately.
         *
         * @param axis Normalized axis vector for projection
         * @return Vector of projections onto the axis
         */
        [[nodiscard]] virtual std::vector<float> project(const infra::math::Vector2 &axis) const = 0;

        /**
         * @brief Returns the centers of all sub-hitboxes, including the main one.
         */
        [[nodiscard]] virtual std::vector<infra::math::Point2> get_centers() const = 0;
    private:
        int strength_ = 0; ///< Strength of the hitbox
    };
}

#endif //PACMAN_HITBOXE_H
