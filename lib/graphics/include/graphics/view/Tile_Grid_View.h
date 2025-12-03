/***************************************************************
 * Project:       Pacman
 * File:          Tile_Grid_View.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-02
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
#ifndef PACMAN_TILE_GRID_VIEW_H
#define PACMAN_TILE_GRID_VIEW_H
#include "Entity_View.h"
#include "Terrain_View.h"

namespace Graphics::View {
    class Tile_Grid_View : public Entity_View {
        std::vector<std::shared_ptr<Terrain_View>> terrains_;

        public:
        explicit Tile_Grid_View(const std::vector<std::shared_ptr<Terrain_View>>& terrain);
        ~Tile_Grid_View() override;

        void render(sf::RenderWindow &window, const Math::Vector2& pixel_pos) const override;
    };
}

#endif //PACMAN_TILE_GRID_VIEW_H