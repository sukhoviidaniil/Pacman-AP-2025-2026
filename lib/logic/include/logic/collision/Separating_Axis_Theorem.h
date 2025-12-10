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

#include "logic/collision/Collision_Control.h"

namespace Logic::Collision {
    class Separating_Axis_Theorem : public Collision_Control {

        bool level_and_strength_check(const std::shared_ptr<HitBoxe>& first, const std::shared_ptr<HitBoxe>& second) const;
        public:

        Separating_Axis_Theorem();

        [[nodiscard]] bool collision(const std::shared_ptr<HitBoxe>& first) const override;

        [[nodiscard]] bool collision(const std::shared_ptr<HitBoxe>& first, const std::shared_ptr<HitBoxe>& second) override;

        [[nodiscard]] std::optional<Math::Vector2> collision_mtv(const std::shared_ptr<HitBoxe>& first, const std::shared_ptr<HitBoxe>& second) override;
    };
    using SAT = Separating_Axis_Theorem;
}

#endif //PACMAN_SEPARATING_AXIS_THEOREM_H