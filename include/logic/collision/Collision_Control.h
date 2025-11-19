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
#include "HitBoxe_Shape.h"
#include <optional>

namespace Logic::Collision {
    class Collision_Control {
        public:
        virtual ~Collision_Control() = default;

        /**
         *
         * @param first
         * @param second
         * @return
         */
        virtual bool collision(const HitBoxe_Shape &first, const HitBoxe_Shape &second) = 0;

        /**
         *
         * @param first
         * @param second
         * @return
         */
        virtual std::optional<Math::Vector2> collision_mtv(const HitBoxe_Shape &first, const HitBoxe_Shape &second) = 0;

    };
}

#endif //PACMAN_COLLISION_CONTROL_H