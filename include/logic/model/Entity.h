/***************************************************************
 * Project:       Pacman
 * File:          Entity.h
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
#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include <memory>

#include "logic/collision/HitBoxe.h"
#include "math/Vector2.h"

namespace Logic::Model {
    class Entity {
    protected:
        Math::Vector2 position_;
        std::shared_ptr<Collision::HitBoxe> hitbox_;
        int status_ = 0;
    public:
        explicit Entity(const Math::Vector2 &position);

        [[nodiscard]] Math::Vector2 get_position() const;
        std::shared_ptr<Collision::HitBoxe> get_hitboxe();
    };
}


#endif //PACMAN_ENTITY_H