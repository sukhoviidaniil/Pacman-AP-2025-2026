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

    /**
     * @brief Rectangular hitbox implementation.
     *
     * Represents an axis-aligned rectangle with a center, width, and height,
     * implementing the HitBox interface.
     */
    class HitBox_Rectangle : public HitBox {
        public:
        /**
         * @brief Constructs a rectangle hitbox with width, height, and strength.
         *
         * @param width Rectangle width
         * @param height Rectangle height
         * @param strength Hitbox strength
         */
        HitBox_Rectangle(float width, float height, int strength);

        /**
         * @brief Constructs a rectangle hitbox with center, width, height, and strength.
         *
         * @param center Center position
         * @param width Rectangle width
         * @param height Rectangle height
         * @param strength Hitbox strength
         */
        HitBox_Rectangle(const infra::math::Point2& center, float width, float height, int strength);

        /**
         * @brief Copy constructor.
         */
        HitBox_Rectangle(const HitBox_Rectangle& other);

        /**
         * @brief Clones the rectangle hitbox.
         */
        [[nodiscard]] std::unique_ptr<HitBox> clone() const override;

        /**
         * @brief Returns the normal vectors for rectangle sides.
         */
        [[nodiscard]] std::vector<infra::math::Vector2> get_normals() const override;

        /**
         * @brief Returns the AABB bounding the rectangle.
         */
        [[nodiscard]] AABB get_aabb() const override;

        /**
         * @brief Moves the rectangle to a new center position.
         *
         * @param newPos Target center position
         */
        void move_to(const  infra::math::Point2& newPos) override;

        /**
         * @brief Projects the rectangle onto a given axis.
         *
         * @param axis Normalized axis vector
         * @return Vector of projections of rectangle corners
         */
        [[nodiscard]] std::vector<float> project(const infra::math::Vector2 &axis) const override;

        /**
         * @brief Returns the center(s) of the rectangle.
         *
         * @return Vector containing the center point
         */
        [[nodiscard]] std::vector<infra::math::Point2> get_centers() const override;

    private:
        infra::math::Point2 center_; ///< Center of the rectangle
        float width_; ///< Width of the rectangle
        float height_; ///< Height of the rectangle
    };
}

#endif //PACMAN_HITBOX_RECTANGLE_H