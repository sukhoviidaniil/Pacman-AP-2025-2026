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
        const std::shared_ptr<Collision::HitBoxe> &hitbox, const unsigned int status, const bool walkable):
    Entity(name, position, hitbox, status), walkable_(walkable){
    }

    Terrain::~Terrain() = default;

    bool Terrain::walkable() const {
        return walkable_;
    }
}

