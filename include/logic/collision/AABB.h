/***************************************************************
 * Project:       Pacman
 * File:          AABB.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-18
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
#ifndef PACMAN_AABB_H
#define PACMAN_AABB_H
#include <limits>


namespace Logic::Collision {
    struct AABB {
        float min_X = std::numeric_limits<float>::max();
        float max_X = -std::numeric_limits<float>::max();
        float min_Y = std::numeric_limits<float>::max();
        float max_Y = -std::numeric_limits<float>::max();
    };
}

#endif //PACMAN_AABB_H