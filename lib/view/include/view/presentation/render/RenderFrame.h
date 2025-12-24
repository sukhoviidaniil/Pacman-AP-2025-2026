/***************************************************************
 * Project:       Pacman
 * File:          RenderFrame.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-24
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
#ifndef PACMAN_AST_RENDERFRAME_H
#define PACMAN_AST_RENDERFRAME_H

#include "view/presentation/render/RenderItem.h"
#include "view/presentation/external/Camera.h"

namespace view::ui {
    struct RenderFrame : RenderNode {
        Camera camera;
        std::vector<RenderItem> constant_items;
        std::vector<RenderItem> temp_items;
    };
}

#endif //PACMAN_AST_RENDERFRAME_H