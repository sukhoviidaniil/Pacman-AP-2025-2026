/***************************************************************
 * Project:       Pacman
 * File:          Collision_Control.h
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

#include "logic/collision/HitBoxe.h"
#include <optional>

namespace Logic::Collision {
    class Collision_Control {
        public:
        virtual ~Collision_Control() = default;


        [[nodiscard]] virtual bool collision(const std::shared_ptr<HitBoxe>& first) const = 0;

        /**
         *
         * @param first
         * @param second
         * @return
         */
        [[nodiscard]] virtual bool collision(const std::shared_ptr<HitBoxe>& first, const std::shared_ptr<HitBoxe>& second) = 0;

        /**
         *
         * @param first
         * @param second
         * @return
         */
        [[nodiscard]] virtual std::optional<Math::Vector2> collision_mtv(const std::shared_ptr<HitBoxe>& first, const std::shared_ptr<HitBoxe>& second) = 0;

    };
}

#endif //PACMAN_COLLISION_CONTROL_H