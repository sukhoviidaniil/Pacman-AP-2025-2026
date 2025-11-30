/***************************************************************
 * Project:       Pacman
 * File:          Collecteble_View.h
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
#ifndef PACMAN_COLLECTEBLE_VIEW_H
#define PACMAN_COLLECTEBLE_VIEW_H



#include "graphics/view/Entity_View.h"
#include "SFML/Graphics/Sprite.hpp"
#include <memory>
namespace Graphics::View {
    class Collecteble_View : public Entity_View {
        std::shared_ptr<sf::Sprite> sprite_;
        public:
        Collecteble_View(const std::shared_ptr<sf::Sprite>& sprite);

        void render(const Math::Vector2& pixel_pos, const std::shared_ptr<sf::Window> &window) const override;
    };
}

#endif //PACMAN_COLLECTEBLE_VIEW_H
