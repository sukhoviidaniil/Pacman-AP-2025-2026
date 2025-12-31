/***************************************************************
 * Project:       Pacman
 * File:          BlinkyTarget.h
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
#ifndef PACMAN_BLINKYTARGET_H
#define PACMAN_BLINKYTARGET_H
#include "TargetStrategy.h"


namespace model::ai {
    struct BlinkyTarget : TargetStrategy {
        TilePos target(const GhostContext& ctx) const override {
            return ctx.pacman_pos;
        }
    };
}
#endif //PACMAN_BLINKYTARGET_H