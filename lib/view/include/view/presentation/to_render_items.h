/***************************************************************
 * Project:       Pacman
 * File:          to_render_items.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-22
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
#ifndef PACMAN_TO_RENDER_ITEMS_H
#define PACMAN_TO_RENDER_ITEMS_H

#include "layout_engine/UIElement.h"

namespace infra::ui {
    inline void collect_render_items(
        const UIElement& element,
        std::vector<RenderItem>& out_items,
        Space space = Space::Screen
    ) {
        if (!element.visible) return;

        RenderItem item;
        item.space = space;
        item.rect = element.result.rect;
        item.sprite = ""; // empty for normal UI, or you can store Label/Button id
        item.status = "";
        item.direction = infra::math::Direction::None;

        out_items.push_back(item);

        for (const auto& child : element.children) {
            collect_render_items(*child, out_items, space);
        }
    }

    inline RenderFrame build_render_frame_from_ui(
        const UIElement& root_ui,
        const Camera& cam
    ) {
        RenderFrame frame;
        frame.camera = cam;
        collect_render_items(root_ui, frame.items, Space::Screen);
        return frame;
    }
}

#endif //PACMAN_TO_RENDER_ITEMS_H