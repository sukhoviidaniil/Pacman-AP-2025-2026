/***************************************************************
 * Project:       Pacman
 * File:          HitBox_Shape.h
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
#ifndef PACMAN_HITBOXE_SHAPE_H
#define PACMAN_HITBOXE_SHAPE_H

#include "model/collision/HitBox.h"

namespace model::collision {
    /**
     * @brief Arbitrary polygonal hitbox implementation.
     *
     * Represents a hitbox defined by a set of points (polygon),
     * implementing the HitBox interface.
     */
    class HitBox_Shape final : public HitBox {
        public:
        /**
         * @brief Constructs a polygonal hitbox from a set of points.
         *
         * @param points Vertices defining the shape
         * @param strength Hitbox strength
         */
        explicit HitBox_Shape(const std::vector<infra::math::Point2> &points, const int& strength);

        /**
         * @brief Constructs a rectangular-shaped polygonal hitbox from position, width, and height.
         *
         * @param pos Top-left or reference position
         * @param height Height of the rectangle
         * @param width Width of the rectangle
         * @param strength Hitbox strength
         */
        explicit HitBox_Shape(const infra::math::Point2 &pos, const float& height, const float& width, const int& strength);

        /**
         * @brief Copy constructor.
         */
        HitBox_Shape(const HitBox_Shape & other);

        /**
         * @brief Destructor.
         */
        ~HitBox_Shape() override;

        /**
         * @brief Clones the polygonal hitbox.
         */
        [[nodiscard]] std::unique_ptr<HitBox> clone() const override;

        /**
         * @brief Returns normal vectors of the polygon's edges.
         */
        [[nodiscard]] std::vector<infra::math::Vector2> get_normals() const override;

        /**
         * @brief Returns the axis-aligned bounding box enclosing the polygon.
         */
        [[nodiscard]] AABB get_aabb() const override;

        /**
         * @brief Moves the polygon to a new position.
         *
         * @param pos New reference position
         */
        void move_to(const infra::math::Point2& pos) override;

        /**
         * @brief Projects the polygon onto a given axis.
         *
         * @param axis Normalized axis vector
         * @return Vector of projections of all vertices
         */
        [[nodiscard]] std::vector<float> project(const infra::math::Vector2 &axis) const override;

        /**
         * @brief Returns the center points of the polygon.
         *
         * @return Vector containing the center(s)
         */
        [[nodiscard]] std::vector<infra::math::Point2> get_centers() const override;
    private:
        std::vector<infra::math::Point2> points_; ///< Vertices defining the polygon
    };
}

#endif //PACMAN_HITBOXE_SHAPE_H