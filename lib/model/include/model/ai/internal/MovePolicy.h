/***************************************************************
 * Project:       Pacman
 * File:          MovePolicy.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-28
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
#ifndef PACMAN_MOVEPOLICY_H
#define PACMAN_MOVEPOLICY_H
#include "infra/math/Direction.h"
#include "infra/math/Vector2.h"


namespace model::ai {
    /// Selects the direction of movement from self_tile to target (following the rules of turning and paths)
    struct MovePolicy {
        virtual ~MovePolicy() = default;

        virtual infra::math::Direction choose_direction(
            // const TileMap&,
            infra::math::Vector2 self,
            infra::math::Vector2 target
        ) const = 0;
    };
}
#endif //PACMAN_MOVEPOLICY_H