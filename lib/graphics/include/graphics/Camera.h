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
#include <vector>


namespace Graphics {

    class Camera {
        unsigned int width_;
        unsigned int height_;

        // center of the logical window (in the logical coordinates of the world)
        Math::Vector2 logic_center_;
        // the point in pixels where the logical center should be on the screen
        Math::Vector2 window_center_;

        float scale_ = 1.0f;

        protected:

        [[nodiscard]] std::optional<Math::Vector2> get_entity_position(const std::shared_ptr<View::Entity_View>& view) const;
        [[nodiscard]] std::vector<std::pair<Math::Vector2, std::shared_ptr<View::Entity_View>>> get_valid_views(const sf::RenderWindow &window, const std::vector<std::shared_ptr<View::Entity_View>> &views) const;

        public:
        Camera(unsigned int width, unsigned int height);

        Camera(unsigned int width, unsigned int height, const Math::Vector2 &logic_center, const Math::Vector2 &window_center);

        void set_width(unsigned int width);
        void set_height(unsigned int height);
        void set_window_center(unsigned int recLeft, unsigned int recTop);
        void set_window_center(const std::shared_ptr<sf::Window>& window);
        void set_window_center(const Math::Vector2 &center);
        void set_logic_center(const Math::Vector2 &center);

        void render(sf::RenderWindow &window, const std::vector<std::shared_ptr<View::Entity_View>> &views) const;
    };
}

#endif //PACMAN_CAMERA_H