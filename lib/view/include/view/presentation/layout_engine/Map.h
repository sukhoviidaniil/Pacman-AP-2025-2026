/***************************************************************
 * Project:       Pacman
 * File:          Map.h
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
#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H
#include "view/presentation/layout_engine/UIElement.h"
#include "view/presentation/render/RI_ComplexSprite.h"
#include "view/presentation/render/RI_Rectangle.h"

namespace view::ui {
    class Map : public UIElement {
    public:

        void append_render_items(RenderFrame& frame, const ViewContext& ctx) const override;

    };
}

#endif //PACMAN_MAP_H