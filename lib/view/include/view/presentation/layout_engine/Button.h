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
#ifndef PACMAN_BUTTON_H
#define PACMAN_BUTTON_H

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
         * @param fill
         * @param border
         * @param border_w
         */
        explicit Button(
            std::string text,
            const infra::ui::Color fill,
            const infra::ui::Color border = {},
            const int border_w = 0
        )
            : Rectangle(fill, border, border_w)
            , text_(std::move(text))
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
            // first, we calculate the size of the text
            const infra::math::Vector2 text_size = label_.measure(avail);

            // minimum button below text
            infra::math::Vector2 size {
                text_size.x + padding.x * 2,
                text_size.y + padding.y * 2
            };

            size.x = std::clamp(size.x, min_size.x, max_size.x);
            size.y = std::clamp(size.y, min_size.y, max_size.y);
            return size;
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
            result.rect = r;

            // center the text
            infra::ui::Rect text_rect (
                r.x + (r.width  - label_.result.rect.width)  * 0.5f,
                r.y + (r.height - label_.result.rect.height) * 0.5f,
                label_.result.rect.width,
                label_.result.rect.height
            );
            label_.layout(text_rect);
        }

        void append_render_items(RenderFrame& frame, const ViewContext& ctx) const override {
            if (!visible) return;

            // determine alpha based on menu status
            infra::ui::Color fill = fill_color;
            infra::ui::Color border = border_color;

            float alpha = 0.75f;
            if (ctx.menu) {
                if (ctx.menu->get().current_button_name() == text_) {
                    alpha = 1.0f;
                }
            }

            fill.a   = static_cast<std::uint8_t>(fill.a   * alpha);
            border.a = static_cast<std::uint8_t>(border.a * alpha);

            // rectangle button (by inheriting from Rectangle)
            auto rect_item = std::make_unique<RI_Rectangle>();
            rect_item->rect = result.rect;
            rect_item->color = fill;
            rect_item->border_color = border;
            rect_item->border_width = border_width;
            frame.constant_items.push_back(std::move(rect_item));

            // text
            label_.append_render_items(frame, ctx);
        }

    private:
        std::string text_;
        Label label_{text_};
        infra::math::Vector2 padding{8.f, 4.f};
    };
}

#endif //PACMAN_BUTTON_H