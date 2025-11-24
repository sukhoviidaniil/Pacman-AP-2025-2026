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
#include "Actor_View.h"

namespace Graphics::View {
    class Terrain_View : public Entity_View {

        std::shared_ptr<sf::Sprite> sprite_;
    public:
        Terrain_View(const std::shared_ptr<sf::Sprite>& sprite);

        void render(const Math::Vector2& pixel_pos, const std::shared_ptr<sf::Window> &window) const override;
    };
}

#endif //PACMAN_TERRAIN_VIEW_H