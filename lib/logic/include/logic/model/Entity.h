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

#include "logic/collision/World_Collision_Manager.h"
#include "math/Vector2.h"

#include <memory>

namespace Logic::Model {
    struct Entity_Info {
        std::string name;
        Math::Vector2 position;
        std::shared_ptr<Collision::HitBoxe> hitbox;
        unsigned int max_status;
    };

    class Entity {
        // Name for identification purposes
        std::string name_;
    protected:
        // Position in world coordinates
        Math::Vector2 position_;

        std::shared_ptr<Collision::HitBoxe> hitbox_;

        // Current status
        unsigned int status_ = 0;
        // The highest status that can be achieved
        unsigned int max_status_;
    public:

        Entity(
            const std::string& name, const Math::Vector2 &position,
            const std::shared_ptr<Collision::HitBoxe> &hitbox, unsigned int max_status
        );

        virtual ~Entity();

        // ===== Getters =====
        [[nodiscard]] virtual std::string get_name() const;
        [[nodiscard]] virtual Math::Vector2 get_position() const;
        virtual std::shared_ptr<Collision::HitBoxe> get_hitboxe();
        [[nodiscard]] virtual unsigned int get_status() const;
        [[nodiscard]] virtual Math::Vector2 get_direction() const;

        // ===== Setters =====
        virtual void set_direction(const Math::Vector2 &direction);

        virtual void move(float deltaTime, const std::shared_ptr<Collision::World_Collision_Manager> &collision_control) = 0;

        [[nodiscard]] virtual bool walkable() const;

        virtual void simulate(float deltaTime, const std::shared_ptr<Collision::World_Collision_Manager> &collision_control) = 0;
    };
}


#endif //PACMAN_ENTITY_H