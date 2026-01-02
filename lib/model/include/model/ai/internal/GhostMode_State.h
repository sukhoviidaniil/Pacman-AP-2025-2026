/***************************************************************
 * Project:       Pacman
 * File:          GhostMode_State.h
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
#ifndef PACMAN_GHOSTMODE_STATE_H
#define PACMAN_GHOSTMODE_STATE_H

namespace model::ai {
    enum class GhostMode {
        Chase,
        Scatter,
        Frightened,
        Dead
    };
}

#endif //PACMAN_GHOSTMODE_STATE_H