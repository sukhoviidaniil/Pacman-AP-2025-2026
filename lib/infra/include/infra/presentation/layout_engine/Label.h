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
#include "Base.h"
#include "UIElement.h"

namespace infra::ui {
    class Label : public UIElement {
    public:

        ~Label() override = default;
        explicit Label(std::string text) : text(std::move(text)) {}

        Vec2 measure(Vec2) override {
            // Conditional: 8px per character
            return { static_cast<float>(text.size() * 8), 16 };
        }

        std::string text;
    };
}

#endif //PACMAN_LABEL_H