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

#include "model/collision/HitBoxe.h"
#include <optional>

namespace model::collision {
    class Collision_Control {
        public:
        virtual ~Collision_Control() = default;

        /**
         *
         * @param first
         * @param second
         * @return
         */
        [[nodiscard]] virtual bool collision(const std::shared_ptr<const HitBoxe>& first, const std::shared_ptr<const HitBoxe>& second) = 0;

        /**
         *
         * @param first
         * @param second
         * @return
         */
        [[nodiscard]] virtual std::optional<math::Vector2> collision_mtv(const std::shared_ptr<const HitBoxe>& first, const std::shared_ptr<const HitBoxe>& second) = 0;

    };
}

#endif //PACMAN_COLLISION_CONTROL_H