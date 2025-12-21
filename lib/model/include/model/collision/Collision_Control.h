/***************************************************************
 * Project:       Pacman
 * File:          collision_Control.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-15
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
#ifndef PACMAN_COLLISION_CONTROL_H
#define PACMAN_COLLISION_CONTROL_H

#include "model/collision/HitBox.h"
#include <optional>

namespace model::collision {
    class Collision_Control {
        public:
        virtual ~Collision_Control() = default;

        [[nodiscard]] virtual bool collision(const HitBox& first,const HitBox& second) const = 0;

        [[nodiscard]] virtual std::optional<infra::math::Vector2> collision_mtv(const HitBox& first, const HitBox& second) const = 0;

    };
}

#endif //PACMAN_COLLISION_CONTROL_H