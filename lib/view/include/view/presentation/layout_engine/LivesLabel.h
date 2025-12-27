/***************************************************************
 * Project:       Pacman
 * File:          LivesLabel.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-26
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
#ifndef PACMAN_LIVESLABEL_H
#define PACMAN_LIVESLABEL_H

#include "view/presentation/render/RI_Label.h"
#include "view/presentation/layout_engine/Text.h"

namespace view::ui {
    class LivesLabel : public Text {
    public:

        void append_render_items(RenderFrame& frame, const ViewContext& ctx) const override {
            if (!visible || !ctx.score) return;

            const auto& score = ctx.score->get();

            int render_size = fontSize;
            if (stretch_font) {
                render_size = static_cast<int>(result.rect.height);
            }

            std::unique_ptr<RI_Label> item = std::make_unique<RI_Label>();
            item->text  = "Lives: " + std::to_string(score.lives_remaining());
            item->font  = font;
            item->color = color;
            item->size  = render_size;
            item->rect  = result.rect;

            frame.constant_items.push_back(std::move(item));
        }
    };
}
#endif //PACMAN_LIVESLABEL_H