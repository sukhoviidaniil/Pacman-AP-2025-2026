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
    Tile::Tile(const std::shared_ptr<Collision::HitBoxe>& hitboxe):
    hitboxe_(hitboxe) {
        std::vector<Math::Vector2> centers = hitboxe_->get_centers();
        if (centers.empty()) throw;
        center_ = hitboxe_->get_centers()[0];
    }

    Tile::Tile(const std::shared_ptr<Collision::HitBoxe> &hitboxe, const Math::Vector2 &t_center):
    hitboxe_(hitboxe), center_(t_center){
    }

    void Tile::set_status(int status) {
        status_ = status;
    }

    int Tile::get_status() const {
        return status_;
    }

    Math::Vector2 Tile::get_center() const {
        return center_;
    }

    std::shared_ptr<Collision::HitBoxe> Tile::get_hitbox() const {
        return hitboxe_;
    }
}
