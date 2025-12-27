/***************************************************************
 * Project:       Pacman
 * File:          Label.h
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
#ifndef PACMAN_LABEL_H
#define PACMAN_LABEL_H

#include "Text.h"
#include "view/presentation/render/RI_Label.h"

namespace view::ui {
    /**
     * @brief Simple text label UI element.
     *
     * Represents a leaf layout element that displays a single line of text.
     * The label participates in the layout system by reporting its desired
     * size based on the text content.
     */
    class Label : public Text {
    public:
        /// @brief Virtual destructor.
        ~Label() override = default;

        /**
         * @brief Constructs a label with the given text.
         *
         * @param text Text content of the label.
         */
        explicit Label(std::string text = "") : text(std::move(text)) {
        }

        explicit Label(std::string text = "", const int fontSize = 24) : Text(fontSize), text(std::move(text)) {
        }

        /**
         * @brief Measures the desired size of the label.
         *
         * Uses a simplified text metric: a fixed width per character
         * and a constant line height.
         *
         * @param available Available space (ignored).
         * @return Desired size of the label.
         */
        infra::math::Vector2 measure(const infra::math::Vector2& available) override {
            // Width = character width * number of characters * font scale
            float char_width = 0.6f * static_cast<float>(fontSize); // approximately, depending on the font
            float width = char_width * static_cast<float>(text.size());

            // Height = font size * line spacing coefficient
            float height = static_cast<float>(fontSize) * 1.2f;

            // Apply min/max restrictions
            width  = std::clamp(width, min_size.x, max_size.x);
            height = std::clamp(height, min_size.y, max_size.y);

            return { width, height };
        }

        void append_render_items(RenderFrame& frame, const ViewContext& ctx) const override {
            if (!visible) return; // skip invisible elements

            std::unique_ptr<RI_Label> item = std::make_unique<RI_Label>();
            item->text = text;
            item->font = font;
            item->color = color;
            item->size = static_cast<int>(fontSize);
            item->rect = result.rect;

            frame.constant_items.push_back(std::move(item));

            // If Label has child elements (rare), add them recursively
            for (const auto& c : children) {
                c->append_render_items(frame, ctx);
            }
        }


        /// @brief Text content of the label.
        std::string text;
    };
}

#endif //PACMAN_LABEL_H