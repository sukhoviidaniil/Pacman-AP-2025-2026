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

#include "infra/math/Point2.h"

#include <memory>

#include "collision/collision_Control.h"

namespace model {
    class Entity {
    public:
        virtual ~Entity();
        Entity(
            std::string   name, const math::Point2 &position, std::unique_ptr<collision::HitBox> hitbox
        );

        // ===== Getters =====
        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] math::Point2 get_position() const;
        [[nodiscard]] const collision::HitBox& get_hitboxe() const;

    protected:
        // Position in world coordinates
        math::Point2 position_;
        // All Entities have some hitbox
        std::unique_ptr<collision::HitBox> hitbox_;
    private:
        // Name for identification purposes
        std::string name_;
    };
}


#endif //PACMAN_ENTITY_H