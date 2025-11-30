/***************************************************************
 * Project:       Pacman
 * File:          Terrain_View.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-24
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

#include "graphics/view/Terrain_View.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Graphics::View {
    Terrain_View::Terrain_View() = default;

    Terrain_View::Terrain_View(const std::shared_ptr<sf::Sprite> &sprite):
    sprite_(sprite){
    }

    void Terrain_View::render(sf::RenderWindow &window, const Math::Vector2 &pixel_pos) const {
        const sf::Vector2f pos = {pixel_pos.x, pixel_pos.y};
        if (sprite_ != nullptr) {
            sprite_->setPosition(pos);
            window.draw(*sprite_);
        }else {
            sf::RectangleShape placeholder(sf::Vector2f(32.f, 32.f));
            placeholder.setPosition(pos);
            placeholder.setFillColor(sf::Color(128, 0, 128));
            window.draw(placeholder);
        }
    }
}
