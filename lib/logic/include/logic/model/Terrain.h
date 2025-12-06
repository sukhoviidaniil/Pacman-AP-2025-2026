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
        public:
        explicit Terrain(
            const std::string &name, const Math::Vector2 &position,
            const std::shared_ptr<Collision::HitBoxe> &hitbox, unsigned int max_status, bool walkable = false);
        ~Terrain() override;

        [[nodiscard]] Math::Vector2 get_direction() const override;

        void set_direction(const Math::Vector2 &direction) override;

        void move(float deltaTime, const std::shared_ptr<Collision::World_Collision_Manager> &collision_control) override;

        [[nodiscard]] bool walkable() const override;
    };
}

#endif
