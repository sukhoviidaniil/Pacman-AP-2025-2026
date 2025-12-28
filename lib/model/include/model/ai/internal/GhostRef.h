/***************************************************************
 * Project:       Pacman
 * File:          GhostRef.h
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
#ifndef PACMAN_GHOSTREF_H
#define PACMAN_GHOSTREF_H
#include <cstddef>

#include "model/ai/internal/GhostRole.h"

namespace model::ai {
    struct GhostRef {
        GhostRole role;
        std::size_t index; // if there are several of them
    };
}

#endif //PACMAN_GHOSTREF_H