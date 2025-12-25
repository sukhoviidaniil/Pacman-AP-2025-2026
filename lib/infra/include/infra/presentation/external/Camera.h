/***************************************************************
 * Project:       Pacman
 * File:          Camera.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-17
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
#ifndef PACMAN_AST_CAMERA_H
#define PACMAN_AST_CAMERA_H


#include "infra/math/Vector2.h"

namespace infra::ui {
    struct Camera {
        /// The size of the screen area in which View draws the scene. Screen pixels
        infra::math::Vector2 viewport_size;
        infra::math::Vector2 position_in_screen; /// Coordinates of the upper left corner of the camera (screen coordinates)
        infra::math::Vector2 position_in_world; /// Coordinates of the upper left corner of the camera (world coordinates)
        float zoom  = 1.0f; ///
    };
}


#endif //PACMAN_AST_CAMERA_H