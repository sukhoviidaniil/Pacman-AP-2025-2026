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
    class Button : public UIElement {
    public:
        ~Button() override = default;
        explicit Button(std::string text) {
            add(std::make_shared<Label>(std::move(text)));
            padding = {8, 4};
        }

        Vec2 measure(Vec2 avail) override {
            Vec2 c = children[0]->measure(avail);
            return {c.x + padding.x * 2, c.y + padding.y * 2};
        }

        void layout(Rect r) override {
            result.rect = r;
            Rect inner {
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