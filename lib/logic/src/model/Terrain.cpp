/***************************************************************
 * Project:       Pacman
 * File:          Terrain.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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

#include "logic/model/Terrain.h"

namespace Logic::Model {
    Terrain::Terrain(
        const std::string &name, const Math::Vector2 &position,
        const std::shared_ptr<Collision::HitBoxe> &hitbox, const unsigned int max_status, const bool walkable):
    Entity(name, position, hitbox, max_status){
        if (max_status < 1) {
            throw std::invalid_argument("Terrain: max_status must be > 1");
        }
        if (walkable) {
            status_ = 1;
        }else {
            status_ = 0;
        }
    }

    Terrain::~Terrain() = default;

    Math::Vector2 Terrain::get_direction() const {
        throw std::invalid_argument("Terrain: can't get direction");
    }

    void Terrain::set_direction(const Math::Vector2 &direction) {
        throw std::invalid_argument("Terrain: can't set direction");
    }

    void Terrain::move(float deltaTime, const std::shared_ptr<Collision::World_Collision_Manager> &collision_control) {
        throw std::invalid_argument("Terrain: can't move to terrain");
    }

    bool Terrain::walkable() const {
        return status_;
    }
}

