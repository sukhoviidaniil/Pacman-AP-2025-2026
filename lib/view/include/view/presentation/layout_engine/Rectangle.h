/***************************************************************
 * Project:       Pacman
 * File:          Rectangle.h
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
#ifndef PACMAN_RECTANGLE_H
#define PACMAN_RECTANGLE_H
#include "view/presentation/layout_engine/UIElement.h"
#include "view/presentation/render/RI_Rectangle.h"
#include "infra/presentation/external/Color.h"

namespace view::ui {

    class Rectangle : public UIElement {
    public:
        explicit Rectangle(
            const infra::ui::Color fill,
            const infra::ui::Color border = {},
            const int border_w = 0
        )
            : fill_color(fill)
            , border_color(border)
            , border_width(border_w)
        {}

        infra::math::Vector2 measure(const infra::math::Vector2& available) override {
            infra::math::Vector2 size = available;

            if (width.type != infra::ui::Size::Type::Auto)
                size.x = resolve(width, available.x);

            if (height.type != infra::ui::Size::Type::Auto)
                size.y = resolve(height, available.y);

            size.x = std::clamp(size.x, min_size.x, max_size.x);
            size.y = std::clamp(size.y, min_size.y, max_size.y);

            return size;
        }

        void append_render_items(RenderFrame& frame, const ViewContext& ctx) const override {
            if (!visible) return;

            std::unique_ptr<RI_Rectangle> item;
            item->rect = result.rect;
            item->color = fill_color;
            item->border_color = border_color;
            item->border_width = border_width;

            frame.constant_items.push_back(std::move(item));

            for (const auto& c : children)
                c->append_render_items(frame, ctx);
        }

        infra::ui::Color fill_color;
        infra::ui::Color border_color;
        int border_width = 0;

    private:
        static float resolve(const infra::ui::Size& s, float avail) {
            if (s.type == infra::ui::Size::Type::Pixel)   return s.value;
            if (s.type == infra::ui::Size::Type::Percent) return avail * s.value;
            return avail;
        }
    };
}


#endif //PACMAN_RECTANGLE_H