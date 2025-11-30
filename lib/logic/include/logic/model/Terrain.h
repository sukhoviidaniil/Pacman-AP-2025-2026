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

#ifndef PACMAN_TERRAIN_H
#define PACMAN_TERRAIN_H
#include "logic/model/Entity.h"

namespace Logic::Model {
    class Terrain : public Entity {

        bool walkable_ = false;

        public:
        explicit Terrain(
            const std::string &name, const Math::Vector2 &position,
            const std::shared_ptr<Collision::HitBoxe> &hitbox, unsigned int status, bool walkable = false);
        ~Terrain() override;

        bool walkable() const;
    };
}

#endif
