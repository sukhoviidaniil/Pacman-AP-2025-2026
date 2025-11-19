/***************************************************************
 * Project:       Pacman
 * File:          Separating_Axis_Theorem.h
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
#ifndef PACMAN_SEPARATING_AXIS_THEOREM_H
#define PACMAN_SEPARATING_AXIS_THEOREM_H
#include <memory>

#include "Collision_Control.h"

namespace Logic::Collision {
    class Separating_Axis_Theorem : public Collision_Control {
        public:

        Separating_Axis_Theorem();

        bool collision(const std::shared_ptr<HitBoxe>& first, const std::shared_ptr<HitBoxe>& second) override;

        bool collision(const HitBoxe_Shape& first, const HitBoxe_Shape& second) override;
        std::optional<Math::Vector2> collision_mtv(const HitBoxe_Shape &first, const HitBoxe_Shape &second) override;
    };
    using SAT = Separating_Axis_Theorem;
}

#endif //PACMAN_SEPARATING_AXIS_THEOREM_H