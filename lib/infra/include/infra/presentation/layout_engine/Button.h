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

#include "Label.h"
#include "UIElement.h"

namespace infra::ui {
    /**
     * @brief Button UI element.
     *
     * A container element that displays a clickable button with text.
     * Internally contains a Label as its child and adds padding around it.
     */
    class Button : public UIElement {
    public:
        /// @brief Virtual destructor.
        ~Button() override = default;

        /**
         * @brief Constructs a button with the given text.
         *
         * Automatically creates a child Label and sets default padding.
         *
         * @param text Text content of the button.
         */
        explicit Button(std::string text) {
            add(std::make_shared<Label>(std::move(text)));
            padding = {8, 4};
        }

        /**
         * @brief Measures the desired size of the button.
         *
         * Calculates the size based on the child Label and adds
         * horizontal and vertical padding.
         *
         * @param avail Available space from the parent.
         * @return Desired size of the button.
         */
        math::Vector2 measure(const math::Vector2 &avail) override {
            math::Vector2 c = children[0]->measure(avail);
            return {c.x + padding.x * 2, c.y + padding.y * 2};
        }

        /**
         * @brief Assigns the final layout rectangle to the button.
         *
         * Stores the final rectangle for the button itself and
         * positions its child Label inside the padded area.
         *
         * @param r Final rectangle assigned by the layout engine.
         */
        void layout(const Rect r) override {
            result.rect = r;
            const Rect inner {
                r.x + padding.x,
                r.y + padding.y,
                r.w - padding.x * 2,
                r.h - padding.y * 2
            };
            children[0]->layout(inner);
        }
    };
}

#endif //PACMAN_BUTTON_H