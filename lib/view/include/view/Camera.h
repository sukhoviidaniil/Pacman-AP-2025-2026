/***************************************************************
 * Project:       Pacman
 * File:          Camera.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-20
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
#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H

#include "view/View.h"
#include "infra/math/Vector2.h"

#include "SFML/graphics.hpp"

#include <memory>
#include <optional>

/*

namespace view {
    class Camera{
        // ===== Expected dimensions =====
        unsigned int base_window_width_{};
        unsigned int base_window_height_{};
        float ratio_x_{};
        float ratio_y_{};
        // The point in pixels where the Camera center should be on the screen
        infra::math::Vector2 window_center_;

        // ===== Expected dimensions =====
        // Camera working area dimensions
        unsigned int camera_width_{};
        unsigned int camera_height_{};
        float camera_half_w_{};
        float camera_half_h_{};

        // Coordinate of the center of the shooting canvas.
        infra::math::Vector2 camera_center_;
        float scale_{};

        void set(
            unsigned int window_width, unsigned int window_height, const infra::math::Vector2 &window_center,
            unsigned int camera_width, unsigned int camera_height, const infra::math::Vector2 &camera_center, float scale);
    protected:

        [[nodiscard]] std::optional<infra::math::Vector2> get_entity_position(const infra::math::Vector2& view) const;
        [[nodiscard]] std::optional<infra::math::Vector2> get_entity_position(const sf::RenderWindow &window, const infra::math::Vector2& view) const;

    public:
        Camera(
            unsigned int window_width, unsigned int window_height, const infra::math::Vector2 &window_center,
            unsigned int camera_width, unsigned int camera_height, const infra::math::Vector2 &camera_center);
        Camera(
            unsigned int window_width, unsigned int window_height, const infra::math::Vector2 &window_center,
            unsigned int camera_width, unsigned int camera_height, const infra::math::Vector2 &camera_center, float scale);

        virtual ~Camera();

        // ===== Update =====
        void update_base_window(unsigned int window_width, unsigned int window_height, const infra::math::Vector2 &window_center);
        void update_window_center(const sf::RenderWindow *window);

        // ===== Render =====
        virtual void render(sf::RenderWindow &window, const std::shared_ptr<View> &view) const;
    };
}
*/
#endif //PACMAN_CAMERA_H