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

#include "graphics/view/entity/Terrain_View.h"

#include <SFML/graphics/RectangleShape.hpp>

namespace graphics::view {

    Terrain_View::Terrain_View(
        const std::shared_ptr<logic::model::Entity> &entity,
        const std::shared_ptr<sf::Sprite> &sprite) : Entity_View(entity), sprite_(sprite) {

        if (sprite_ == nullptr) {
            placeholder_ = std::make_shared<sf::RectangleShape>(sf::Vector2f(30.f, 30.f));
            placeholder_->setOrigin(17.5f, 17.5f);
            if (name_ == "Wall") {
                placeholder_->setFillColor(sf::Color(0, 0, 255));
            }else {
                placeholder_->setFillColor(sf::Color(0, 0, 0));
            }
        }
    }

    Terrain_View::~Terrain_View() = default;


    void Terrain_View::render(sf::RenderWindow &window, const math::Vector2 &pixel_pos) const {
        const sf::Vector2f pos = {pixel_pos.x, pixel_pos.y};
        if (sprite_ != nullptr) {
            sprite_->setPosition(pos);
            window.draw(*sprite_);
        }else {
            placeholder_->setPosition(pos);
            window.draw(*placeholder_);
        }
    }
}
