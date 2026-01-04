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
    /**
     * @brief Clyde's targeting strategy: normally heads toward Pac-Man, but switches behavior
     *        based on distance or mode (e.g., may retreat if too close). Here we default to Pac-Man.
     */
    struct ClydeTarget : TargetStrategy {
        [[nodiscard]] TilePos target(
            const GlobalGhostContext& g_ctx,
            const UniqGhostContext& u_ctx
            ) const override {
            // like Blinky, but behavior switches to Move/Mode
            return g_ctx.pacman_pos;
        }
    };
}
#endif //PACMAN_CLYDETARGET_H