/***************************************************************
 * Project:       Pacman
 * File:          TargetStrategy.h
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
#ifndef PACMAN_TARGETSTRATEGY_H
#define PACMAN_TARGETSTRATEGY_H
#include "model/ai/GhostContext.h"
#include "infra/math/Vector2.h"

namespace model::ai {
    /// Calculates the target cell for Chase/Scatter mode
    struct TargetStrategy {
        virtual ~TargetStrategy() = default;
        virtual infra::math::Vector2 target(const GhostContext&) const = 0;
    };
}

#endif //PACMAN_TARGETSTRATEGY_H