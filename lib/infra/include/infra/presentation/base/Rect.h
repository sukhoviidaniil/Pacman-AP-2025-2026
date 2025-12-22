/***************************************************************
 * Project:       Pacman
 * File:          Base.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-19
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
#ifndef PACMAN_RECT_H
#define PACMAN_RECT_H

#pragma once
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>
#include <cassert>

#include "infra/math/Point2.h"
#include "infra/math/Vector2.h"

namespace infra::ui {
    /**
     * @brief Axis-aligned rectangle in layout coordinates.
     *
     * Used internally by the layout engine to represent the final
     * position and size of UI elements.
     */
    struct Rect {
        math::Point2 p; ///< X position (left) | Y position (top)
        math::Vector2 v; ///< Width | Height
    };
}
#endif //PACMAN_RECT_H