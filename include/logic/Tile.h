/***************************************************************
 * Project:       Pacman
 * File:          Tile.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-10-23
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
#ifndef PACMAN_TILE_H
#define PACMAN_TILE_H
#include <memory>

#include "core/Entity.h"
namespace Logic {
    class Tile {
        Math::Vector2 center;
        int status = 0;
        std::shared_ptr<Core::Entity> my_entity;
    public:
        explicit Tile(const Math::Vector2 &t_center);
        [[nodiscard]] Math::Vector2 get_center() const;
        [[nodiscard]] std::shared_ptr<Core::Entity> occupied() const;
    };
}

#endif //PACMAN_TILE_H