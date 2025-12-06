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

#include "graphics/view/Entity_View.h"
#include "math/Vector2.h"

#include "SFML/Graphics.hpp"

#include <memory>


namespace Graphics {
    class Camera{
        // ===== Expected dimensions =====
        unsigned int base_window_width_ = 1000;
        unsigned int base_window_height_ = 1000;
        float ratio_x_ = 0.5f;
        float ratio_y_ = 0.5f;
        // The point in pixels where the Camera center should be on the screen
        Math::Vector2 window_center_;

        // ===== Expected dimensions =====
        // Camera working area dimensions
        unsigned int camera_width_ = 100;
        unsigned int camera_height_ = 100;
        float camera_half_w_;
        float camera_half_h_;

        // Coordinate of the center of the shooting canvas.
        Math::Vector2 camera_center_;
        float scale_ = 1.0f;
    protected:

        [[nodiscard]] std::optional<Math::Vector2> get_entity_position(const Math::Vector2& view) const;
        [[nodiscard]] std::optional<Math::Vector2> get_entity_position(const sf::RenderWindow &window, const Math::Vector2& view) const;

    public:
        Camera(
            unsigned int window_width, unsigned int window_height, const Math::Vector2 &window_center,
            unsigned int camera_width, unsigned int camera_height, const Math::Vector2 &camera_center);
        Camera(
            unsigned int window_width, unsigned int window_height, const Math::Vector2 &window_center,
            unsigned int camera_width, unsigned int camera_height, const Math::Vector2 &camera_center, float scale);

        virtual ~Camera();

        // ===== Update =====
        void update_base_window(unsigned int window_width, unsigned int window_height, const Math::Vector2 &window_center);
        void update_window_center(const sf::RenderWindow *window);

        // ===== Render =====
        virtual void render(sf::RenderWindow &window, const std::shared_ptr<View::View> &view) const;
    };
}

#endif //PACMAN_CAMERA_H