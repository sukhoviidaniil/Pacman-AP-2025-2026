/***************************************************************
 * Project:       Pacman
 * File:          Camera.cpp
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


#include "view/Camera.h"

namespace view {
    /*
    void Camera::set(
        const unsigned int window_width, const unsigned int window_height, const infra::math::Vector2 &window_center,
        const unsigned int camera_width, const unsigned int camera_height, const infra::math::Vector2 &camera_center, const float scale
        ) {
        if (window_height == 0) {
            throw std::runtime_error("Invalid Camera window_height!");
        }
        if (window_width == 0) {
            throw std::runtime_error("Invalid Camera window_width!");
        }
        if (camera_height == 0) {
            throw std::runtime_error("Invalid Camera camera_height!");
        }
        if (camera_width == 0) {
            throw std::runtime_error("Invalid Camera camera_width!");
        }
        if (scale == 0) {
            throw std::runtime_error("Invalid Camera scale!");
        }
        camera_width_ = camera_width;
        camera_height_ = camera_height;
        camera_center_ = camera_center;
        scale_ = scale;
        camera_half_w_ = static_cast<float>(camera_width_) * 0.5f;
        camera_half_h_ = static_cast<float>(camera_height_) * 0.5f;
        update_base_window(window_width, window_height, window_center);
    }

    std::optional<infra::math::Vector2> Camera::get_entity_position(const infra::math::Vector2 &view) const {
        // Translation of logical position to screen position
        const infra::math::Vector2 delta = (view - camera_center_) * scale_;
        infra::math::Vector2 screen_pos = window_center_ + delta;

        // screen_pos.y = window_center_.y - (screen_pos.y - window_center_.y);

        // Checking for entry into the working area
        if (screen_pos.x < window_center_.x - camera_half_w_ ||
            screen_pos.x > window_center_.x + camera_half_w_ ||
            screen_pos.y < window_center_.y - camera_half_h_ ||
            screen_pos.y > window_center_.y + camera_half_h_)
        {
            return std::nullopt;
        }
        return screen_pos;
    }

    std::optional<infra::math::Vector2> Camera::get_entity_position(const sf::RenderWindow &window, const infra::math::Vector2 &view) const {
        std::optional<infra::math::Vector2> screen_pos = get_entity_position(view);
        if (!screen_pos) return std::nullopt;

        const sf::Vector2u window_size = window.getSize();
        const auto w = static_cast<float>(window_size.x);
        const auto h = static_cast<float>(window_size.y);

        // Checking for entry into the window area
        if (screen_pos->x < 0 ||
            screen_pos->x > w ||
            screen_pos->y < 0 ||
            screen_pos->y > h)
        {
            return std::nullopt;
        }
        return screen_pos;
    }

    Camera::Camera(
        const unsigned int window_width, const unsigned int window_height, const infra::math::Vector2 &window_center,
        const unsigned int camera_width, const unsigned int camera_height, const infra::math::Vector2 &camera_center
        )
    {
        set(window_width, window_height, window_center, camera_width, camera_height, camera_center, 1);
    }

    Camera::Camera(
        const unsigned int window_width, const unsigned int window_height, const infra::math::Vector2& window_center,
        const unsigned int camera_width, const unsigned int camera_height, const infra::math::Vector2& camera_center,
        const float scale
        )
    {
        set(window_width, window_height, window_center, camera_width, camera_height, camera_center, scale);
    }


    Camera::~Camera() = default;

    void Camera::update_base_window(
        const unsigned int window_width, const unsigned int window_height, const infra::math::Vector2 &window_center)
    {
        base_window_width_ = window_width;
        base_window_height_ = window_height;
        // shares relative to the base window (fixed “ideal” proportions)
        ratio_x_ = window_center.x / static_cast<float>(window_width);
        ratio_y_ = window_center.y / static_cast<float>(window_height);
        window_center_ = window_center;
    }

    void Camera::update_window_center(const sf::RenderWindow *window) {
        // calculate the center for the new dimensions
        const auto size = window->getSize();
        window_center_.x = static_cast<float>(size.x)  * ratio_x_;
        window_center_.y = static_cast<float>(size.y) * ratio_y_;
    }

    void Camera::render(sf::RenderWindow &window, const std::shared_ptr<View> &view) const {

        const math::Vector2 pos = view->get_position();
        std::optional<math::Vector2> screen_pos = get_entity_position(window, pos);
        if (!screen_pos) return;
        view->render(window, *screen_pos);

    }*/
}
