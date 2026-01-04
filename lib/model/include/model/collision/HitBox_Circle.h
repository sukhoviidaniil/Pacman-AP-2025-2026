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
    /**
     * @brief Circular hitbox implementation.
     *
     * Represents a circle with a center and radius, implementing all
     * HitBox interface methods.
     */
    class HitBox_Circle final : public HitBox {

    public:
        /**
         * @brief Constructs a circular hitbox.
         *
         * @param strength Hitbox strength
         * @param center Center position of the circle
         * @param radius Radius of the circle
         */
        explicit HitBox_Circle(const int& strength, const infra::math::Point2 &center, const float& radius);
        /**
         * @brief Copy constructor.
         */
        HitBox_Circle(const HitBox_Circle & other);\

        /**
         * @brief Destructor.
         */
        ~HitBox_Circle() override;

        /**
         * @brief Moves the circle to a new position.
         */
        void move_to(const infra::math::Point2 &pos) override;

        /**
         * @brief Clones the circular hitbox.
         */
        [[nodiscard]] std::unique_ptr<HitBox> clone() const override;

        /**
         * @brief Returns the AABB that bounds the circle.
         */
        [[nodiscard]] AABB get_aabb() const override;

        /**
         * @brief Returns normal vectors for collision detection.
         */
        [[nodiscard]] std::vector<infra::math::Vector2> get_normals() const override;

        /**
         * @brief Returns vectors from this circle's center to another hitbox's centers.
         */
        [[nodiscard]] std::vector<infra::math::Vector2> get_vector_to(const HitBox &hit_boxe) const override;

        /**
         * @brief Projects the circle onto a given axis.
         */
        [[nodiscard]] std::vector<float> project(const infra::math::Vector2 &axis) const override;

        /**
         * @brief Returns the center of the circle as a single-element vector.
         */
        [[nodiscard]] std::vector<infra::math::Point2> get_centers() const override;
    private:
        infra::math::Point2 center_; ///< Circle center
        float radius_; ///< Circle radius
    };
}

#endif //PACMAN_HITBOXE_CIRCLE_H