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

#include "graphics/Camera.h"

namespace Graphics {
    std::optional<Math::Vector2> Camera::get_entity_position(const std::shared_ptr<View::Entity_View> &view) const {
        if (!view) return std::nullopt;

        // Position of an entity in global coordinates
        const Math::Vector2 world_pos = view->get_position();

        // Translation into logical coordinates relative to the logical center
        const Math::Vector2 logic_pos = world_pos - logic_center_;

        // Checking for exit beyond the boundaries of the logical window
        const float half_w = static_cast<float>(width_) * 0.5f;
        const float half_h = static_cast<float>(height_) * 0.5f;
        if (logic_pos.x < -half_w || logic_pos.x > half_w ||
            logic_pos.y < -half_h || logic_pos.y > half_h){
            return std::nullopt;
            }

        // Converting logical offset to pixels
        const Math::Vector2 pixel_delta = logic_pos * scale_;

        // Final position in pixels relative to the center of the window
        Math::Vector2 window_pos = window_center_ + pixel_delta;

        return window_pos;
    }

    std::vector<std::pair<Math::Vector2, std::shared_ptr<View::Entity_View>>> Camera::get_valid_views(const sf::RenderWindow &window, const std::vector<std::shared_ptr<View::Entity_View>> &views) const {

        std::vector<std::pair<Math::Vector2, std::shared_ptr<View::Entity_View>>> result;

        const sf::Vector2u window_size = window.getSize();
        const auto win_width = static_cast<float>(window_size.x);
        const auto win_height = static_cast<float>(window_size.y);

        for (const auto &view : views) {
            if (!view) continue;

            auto maybe_pos = get_entity_position(view);
            if (!maybe_pos) continue;
            const Math::Vector2 &pos = *maybe_pos;

            if (pos.x < 0.0f || pos.x > win_width || pos.y < 0.0f || pos.y > win_height) {
                continue;
            }
            result.emplace_back(pos, view);
        }
        return result;
    }

    Camera::Camera(const unsigned int width, const unsigned int height):
    width_(width), height_(height){
    }

    Camera::Camera(const unsigned int width, const unsigned int height, const Math::Vector2 &logic_center, const Math::Vector2 &window_center):
    width_(width), height_(height), logic_center_(logic_center), window_center_(window_center){
    }

    void Camera::set_width(unsigned int width) {
        width_ = width;
    }

    void Camera::set_height(unsigned int height) {
        height_ = height;
    }

    void Camera::set_window_center(const unsigned int recLeft, const unsigned int recTop) {
        window_center_ = Math::Vector2(static_cast<float>(recLeft+width_), static_cast<float>(recTop+height_));
    }

    void Camera::set_window_center(const std::shared_ptr<sf::Window> &window) {
        const float w_width = static_cast<float>(window->getSize().x);
        const float w_height = static_cast<float>(window->getSize().y);
        window_center_ = Math::Vector2(w_width / 2, w_height / 2);
    }

    void Camera::set_window_center(const Math::Vector2 &center) {
        window_center_ = center;
    }

    void Camera::set_logic_center(const Math::Vector2 &center) {
        logic_center_ = center;
    }


    void Camera::render(sf::RenderWindow &window, const std::vector<std::shared_ptr<View::Entity_View>> &views) const {
        const std::vector<
            std::pair<
                Math::Vector2,
                std::shared_ptr<View::Entity_View>
            >
        > views_to_render = get_valid_views(window, views);

        for (const auto &[pos, view] : views_to_render) {
            view->render(window, pos);
        }
    }
}
