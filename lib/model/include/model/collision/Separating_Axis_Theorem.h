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

#include "model/collision/collision_Control.h"

namespace model::collision {
    class Separating_Axis_Theorem : public Collision_Control {

        public:

        Separating_Axis_Theorem();

        [[nodiscard]] bool collision(const HitBox& first, const HitBox& second) const override;

        [[nodiscard]] std::optional<math::Vector2> collision_mtv(const HitBox& first, const HitBox& second) const override;
    };
}

#endif //PACMAN_SEPARATING_AXIS_THEOREM_H