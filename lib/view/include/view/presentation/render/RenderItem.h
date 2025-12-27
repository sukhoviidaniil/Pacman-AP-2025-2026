/***************************************************************
 * Project:       Pacman
 * File:          RenderItem.h
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
#ifndef PACMAN_AST_RENDERITEM_H
#define PACMAN_AST_RENDERITEM_H
#include "infra/presentation/external/Rect.h"
#include "view/presentation/render/RenderNode.h"

namespace view::ui {
    enum class Space {
        Screen,   // UI, HUD
        World     // game logic
    };
    struct RenderItem : RenderNode {
        /// Element dimensions
        infra::ui::Rect rect{};
    };
}

#endif //PACMAN_AST_RENDERITEM_H
