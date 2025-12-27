/***************************************************************
 * Project:       Pacman
 * File:          Text.h
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
#ifndef PACMAN_TEXT_H
#define PACMAN_TEXT_H
#include "UIElement.h"
#include "infra/presentation/external/Color.h"


namespace view::ui {
    /**
     * @brief Simple text label UI element.
     *
     */
    class Text : public UIElement {
    public:
        /// @brief Virtual destructor.
        ~Text() override = default;
        Text() = default;
        explicit Text(const int fontSize) : fontSize(fontSize){}


        /**
         * @brief Measures the desired size of the text.
         *
         * Uses a simplified text metric: a fixed width per character
         * and a constant line height.
         *
         * @param available Available space.
         * @return Desired size of the text.
         */
        infra::math::Vector2 measure(const infra::math::Vector2& available) override {
            return available;
        }


        infra::ui::Color color = infra::ui::Color(255,255,255);

        std::string font = "Arial";

        int fontSize = 14;

        bool stretch_font = false;
    };
}

#endif //PACMAN_TEXT_H