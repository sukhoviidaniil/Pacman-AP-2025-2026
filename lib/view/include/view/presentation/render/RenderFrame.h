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

namespace view::ui {
    struct RenderFrame : infra::ast::Node {
        std::vector<std::unique_ptr<RenderItem>> constant_items;
        std::vector<std::unique_ptr<RenderItem>> temp_items;
    };
}

#endif //PACMAN_AST_RENDERFRAME_H