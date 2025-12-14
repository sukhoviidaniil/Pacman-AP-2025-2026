/***************************************************************
 * Project:       Pacman
 * File:          Terrain_View.h
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
#ifndef PACMAN_TERRAIN_VIEW_H
#define PACMAN_TERRAIN_VIEW_H

#include "graphics/view/Entity_View.h"
#include <SFML/graphics/RectangleShape.hpp>
#include <SFML/graphics/Sprite.hpp>
#include <memory>

namespace graphics::view {
    class Terrain_View : public Entity_View {
        std::shared_ptr<sf::RectangleShape> placeholder_ = nullptr;
        std::shared_ptr<sf::Sprite> sprite_ = nullptr;
    public:
        Terrain_View(const std::shared_ptr<logic::model::Entity>& entity, const std::shared_ptr<sf::Sprite>& sprite);
        ~Terrain_View() override;

        void render(sf::RenderWindow &window, const math::Vector2& pixel_pos) const override;
    };
}

#endif //PACMAN_TERRAIN_VIEW_H