/***************************************************************
 * Project:       Pacman
 * File:          ClydeTarget.h
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
#ifndef PACMAN_CLYDETARGET_H
#define PACMAN_CLYDETARGET_H
#include "TargetStrategy.h"

namespace model::ai {
    struct ClydeTarget : TargetStrategy {
        infra::math::Vector2 target(const GhostContext& ctx) const override {
            // как Blinky, но поведение переключается в Move/Mode
            return ctx.pacman_tile;
        }
    };
}
#endif //PACMAN_CLYDETARGET_H