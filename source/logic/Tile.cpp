/***************************************************************
 * Project:       Pacman
 * File:          Tile.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-05
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

#include "logic/Tile.h"

namespace Logic {
    Tile::Tile(const Math::Vector2 &t_center) : center(t_center) {
    }

    Math::Vector2 Tile::get_center() const {
        return center;
    }

    std::shared_ptr<Core::Entity> Tile::occupied() const {
        return my_entity;
    }
}
