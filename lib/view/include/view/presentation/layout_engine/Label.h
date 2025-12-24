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

#include "view/presentation/layout_engine/UIElement.h"

namespace view::ui {
    /**
     * @brief Simple text label UI element.
     *
     * Represents a leaf layout element that displays a single line of text.
     * The label participates in the layout system by reporting its desired
     * size based on the text content.
     */
    class Label : public UIElement {
    public:
        /// @brief Virtual destructor.
        ~Label() override = default;

        /**
         * @brief Constructs a label with the given text.
         *
         * @param text Text content of the label.
         */
        explicit Label(std::string text) : text(std::move(text)) {}

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
            // Conditional: 8px per character
            return { static_cast<float>(text.size() * 8), 16 };
        }

        /// @brief Text content of the label.
        std::string text;
    };
}

#endif //PACMAN_LABEL_H