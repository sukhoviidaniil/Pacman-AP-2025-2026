/***************************************************************
 * Project:       Pacman
 * File:          Animation.h
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
#ifndef PACMAN_AST_ANIMATION_H
#define PACMAN_AST_ANIMATION_H
#include "infra/ast/Node.h"

namespace infra::ast {
    /**
     * @brief Represents animation settings for a sprite.
     *
     * Inherits from Node and defines the number of frames,
     * duration per frame, and incremental offsets for sprite rectangles.
     */
    struct Animation : Node {
        size_t size = 0; ///< Number of frames in the animation
        float frame_duration = 1.f; ///< Duration of each frame
        int recLeft_increase = 0; ///< Increment for left coordinate per frame
        int recTop_increase = 0; ///< Increment for top coordinate per frame
    };
}

#endif //PACMAN_AST_ANIMATION_H