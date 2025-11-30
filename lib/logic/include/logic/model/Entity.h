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

#include "logic/collision/HitBoxe.h"
#include "math/Vector2.h"

#include <memory>

namespace Logic::Model {
    class Entity {
        std::string name_;
    protected:
        Math::Vector2 position_;
        std::shared_ptr<Collision::HitBoxe> hitbox_;
        unsigned int status_ = 0;
    public:

        Entity(std::string name, const Math::Vector2 &position,
            const std::shared_ptr<Collision::HitBoxe> &hitbox, unsigned int status);

        explicit Entity(const Math::Vector2 & vector2);

        virtual ~Entity();


        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] Math::Vector2 get_position() const;
        std::shared_ptr<Collision::HitBoxe> get_hitboxe();
        [[nodiscard]] unsigned int get_status() const;
    };
}


#endif //PACMAN_ENTITY_H