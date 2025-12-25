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

namespace infra::ui {
    /**
     * @brief Axis-aligned rectangle in layout coordinates.
     *
     * Used internally by the layout engine to represent the final
     * position and size of UI elements.
     */
    struct Rect {
        float x; ///< X position (left)
        float y; ///< Y position (top)
        float width; ///< Width
        float height; ///< Height
    };
}
#endif //PACMAN_RECT_H