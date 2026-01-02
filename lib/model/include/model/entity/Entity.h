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

#include "model/collision/HitBox.h"
#include "infra/presentation/external/Rect.h"

namespace model {
    class Entity {
    public:
        virtual ~Entity();
        Entity(
            std::string name, float size, const infra::math::Point2 &position, std::unique_ptr<collision::HitBox> hitbox
        );

        // ===== Getters =====
        [[nodiscard]] std::string name() const;
        [[nodiscard]] float size() const;
        [[nodiscard]] infra::math::Point2 position() const;
        [[nodiscard]] const collision::HitBox& hitboxe() const;
        [[nodiscard]] infra::ui::Rect rect() const;

    protected:
        // Position in world coordinates
        infra::math::Point2 position_;
        // All Entities have some hitbox
        std::unique_ptr<collision::HitBox> hitbox_;
        float sprite_size_;

        // Name for identification purposes
        std::string name_;
    };
}


#endif //PACMAN_ENTITY_H