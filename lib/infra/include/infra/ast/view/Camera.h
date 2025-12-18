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
#include "../Node.h"
#include "infra/math/Vector2.h"

namespace infra::ast {
    struct Camera : View_Node{
        unsigned int window_width = 0;
        unsigned int window_height = 0;
        math::Vector2 window_center;
        unsigned int camera_width = 0;
        unsigned int camera_height = 0;
        math::Vector2 camera_center;
        float scale = 1.0f;
    };
}

#endif //PACMAN_AST_CAMERA_H