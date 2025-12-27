/***************************************************************
 * Project:       Pacman
 * File:          Button.h
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
#ifndef PACMAN_UI_BUTTON_H
#define PACMAN_UI_BUTTON_H

#include "view/presentation/layout_engine/Label.h"
#include "view/presentation/layout_engine/Rectangle.h"

namespace view::ui {
    /**
     * @brief Button UI element.
     *
     * A container element that displays a clickable button with text.
     * Internally contains a Label as its child and adds padding around it.
     */
    class Button : public Rectangle {
    public:
        /// @brief Virtual destructor.
        ~Button() override = default;

        /**
         * @brief Constructs a button with the given text.
         *
         * Automatically creates a child Label and sets default padding.
         *
         * @param text Text content of the button.
         * @param fontSize
         * @param fill
         * @param border
         * @param border_w
         */
        explicit Button(
            const std::string &text,
            const int fontSize,
            const infra::ui::Color fill,
            const infra::ui::Color border = {},
            const int border_w = 0
        )
            : Rectangle(fill, border, border_w)
            , label_(text, fontSize)
        {}

        /**
         * @brief Measures the desired size of the button.
         *
         * Calculates the size based on the child Label and adds
         * horizontal and vertical padding.
         *
         * @param avail Available space from the parent.
         * @return Desired size of the button.
         */
        infra::math::Vector2 measure(const infra::math::Vector2& avail) override {
            infra::math::Vector2 inner_avail{
                std::max(0.f, avail.x - padding.x * 2.f),
                std::max(0.f, avail.y - padding.y * 2.f)
            };

            infra::math::Vector2 text_size = label_.measure(inner_avail);

            infra::math::Vector2 size{
                text_size.x + padding.x * 2.f,
                text_size.y + padding.y * 2.f
            };

            // применяем правила Rectangle (width/height/min/max/border)
            infra::math::Vector2 resolved = Rectangle::measure(size);
            return resolved;
        }

        /**
         * @brief Assigns the final layout rectangle to the button.
         *
         * Stores the final rectangle for the button itself and
         * positions its child Label inside the padded area.
         *
         * @param r Final rectangle assigned by the layout engine.
         */
        void layout(const infra::ui::Rect r) override {
            // layout самого прямоугольника
            Rectangle::layout(r);

            infra::ui::Rect inner{
                r.x + padding.x,
                r.y + padding.y,
                std::max(0.f, r.width  - padding.x * 2.f),
                std::max(0.f, r.height - padding.y * 2.f)
            };

            // измеряем и размещаем текст
            infra::math::Vector2 ts = label_.measure(
                {inner.width, inner.height}
            );

            infra::ui::Rect text_rect{
                inner.x + (inner.width  - ts.x) * 0.5f,
                inner.y + (inner.height - ts.y) * 0.5f,
                ts.x,
                ts.y
            };

            label_.layout(text_rect);
        }

        void append_render_items(RenderFrame& frame, const ViewContext& ctx) const override {
            if (!visible) return;

            infra::ui::Color fill   = fill_color;
            infra::ui::Color border = border_color;

            float alpha = 0.25f;
            if (ctx.menu) {
                std::string t = ctx.menu->get().current_button_name();
                if (t==label_.text) {
                    alpha = 1.f;
                }
            }


            fill.a   = static_cast<std::uint8_t>(fill.a   * alpha);

            auto rect_item = std::make_unique<RI_Rectangle>();
            rect_item->rect = result.rect;
            rect_item->color = fill;
            rect_item->border_color = border;
            rect_item->border_width = border_width;
            frame.constant_items.push_back(std::move(rect_item));

            label_.append_render_items(frame, ctx);
        }

    private:
        Label label_;
        infra::math::Vector2 padding{8.f, 4.f};
    };
}

#endif //PACMAN_UI_BUTTON_H