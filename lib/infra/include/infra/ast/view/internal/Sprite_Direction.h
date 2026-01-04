/***************************************************************
 * Project:       Pacman
 * File:          Sprite_Direction.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-09
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
#ifndef PACMAN_EXPRESSION_INFO_H
#define PACMAN_EXPRESSION_INFO_H

#include "infra/ast/Node.h"
#include "infra/math/Direction.h"

namespace infra::ast {
    /**
     * @brief Represents the direction and optional sprite coordinates.
     *
     * Inherits from Node and stores a direction along with
     * optional rectangle offsets for sprite rendering.
     */
    struct Sprite_Direction : Node {
        math::Direction direction; ///< Direction of the sprite
        int recLeft = -1; ///< Optional left coordinate in sprite sheet
        int recTop = -1; ///< Optional top coordinate in sprite sheet
    };
}

#endif //PACMAN_EXPRESSION_INFO_H