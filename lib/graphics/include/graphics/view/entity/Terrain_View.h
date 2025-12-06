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


#include <SFML/Graphics/Sprite.hpp>
#include "graphics/view/Entity_View.h"
#include <memory>

#include "logic/model/Actor.h"
#include "SFML/Graphics/RectangleShape.hpp"

namespace Graphics::View {
    class Terrain_View : public Entity_View {
        std::shared_ptr<sf::RectangleShape> placeholder_ = nullptr;
        std::shared_ptr<sf::Sprite> sprite_ = nullptr;
    public:
        Terrain_View(const std::shared_ptr<Logic::Model::Entity>& entity, const std::shared_ptr<sf::Sprite>& sprite);
        ~Terrain_View() override;

        void render(sf::RenderWindow &window, const Math::Vector2& pixel_pos) const override;
    };
}

#endif //PACMAN_TERRAIN_VIEW_H