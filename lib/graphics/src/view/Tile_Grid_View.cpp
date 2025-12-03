/***************************************************************
 * Project:       Pacman
 * File:          Tile_Grid_View.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-03
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

#include "graphics/view/Tile_Grid_View.h"

namespace Graphics {

    View::Tile_Grid_View::Tile_Grid_View(const std::vector<std::shared_ptr<Terrain_View>> &terrain) : terrains_(terrain) {
    }

    View::Tile_Grid_View::~Tile_Grid_View() = default;

    void View::Tile_Grid_View::render(sf::RenderWindow &window, const Math::Vector2 &pixel_pos) const {

    }
}

