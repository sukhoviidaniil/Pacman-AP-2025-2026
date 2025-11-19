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

#include "collision/HitBoxe_Shape.h"

namespace Logic {
    class Tile {
        std::shared_ptr<Collision::HitBoxe> hitboxe_;
        Math::Vector2 center_;
        int status_ = 0;
    public:
        explicit Tile(const std::shared_ptr<Collision::HitBoxe>& hitboxe);
        explicit Tile(const std::shared_ptr<Collision::HitBoxe> &hitboxe, const Math::Vector2 &t_center);
        void set_status(int status);
        [[nodiscard]] int get_status() const;
        [[nodiscard]] Math::Vector2 get_center() const;
        [[nodiscard]] std::shared_ptr<Collision::HitBoxe> get_hitbox() const;

    };
}

#endif //PACMAN_TILE_H