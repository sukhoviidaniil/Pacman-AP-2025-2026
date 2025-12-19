/***************************************************************
 * Project:       Pacman
 * File:          LinearLayout.h
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
#ifndef PACMAN_LINEARLAYOUT_H
#define PACMAN_LINEARLAYOUT_H
#include "Alignment.h"
#include "Base.h"
#include "UIElement.h"


namespace infra::ui {
    class LinearLayout : public UIElement {
    public:
        Align align = Align::Start;
        float spacing = 0.f;

    protected:
        virtual bool horizontal() const = 0;

        Vec2 measure(Vec2 available) override {
            Vec2 total {0, 0};

            for (auto& c : children) {
                if (!c->visible) continue;

                Vec2 cs = c->measure(available);

                if (horizontal()) {
                    total.x += cs.x + spacing;
                    total.y = std::max(total.y, cs.y);
                } else {
                    total.y += cs.y + spacing;
                    total.x = std::max(total.x, cs.x);
                }
            }

            return total;
        }

        void layout(Rect r) override {
            result.rect = r;

            float main = horizontal() ? r.w : r.h;
            float cross = horizontal() ? r.h : r.w;

            float fixed = 0;
            float flex_sum = 0;

            for (auto& c : children) {
                if (!c->visible) continue;
                if (c->flex > 0) flex_sum += c->flex;
                else {
                    Vec2 s = c->measure({r.w, r.h});
                    fixed += horizontal() ? s.x : s.y;
                }
            }

            const float free = main - fixed - spacing * (static_cast<float>(children.size()) - 1);
            float cursor = horizontal() ? r.x : r.y;

            for (const auto& c : children) {
                if (!c->visible) continue;

                Vec2 s = c->measure({r.w, r.h});

                float main_size =
                    c->flex > 0 ? free * (c->flex / flex_sum)
                                : (horizontal() ? s.x : s.y);

                float cross_size =
                    align == Align::Stretch ? cross
                    : (horizontal() ? s.y : s.x);

                Rect cr;

                if (horizontal()) {
                    cr = {cursor, r.y, main_size, cross_size};
                } else {
                    cr = {r.x, cursor, cross_size, main_size};
                }

                c->layout(cr);
                cursor += main_size + spacing;
            }
        }
    };
}
#endif //PACMAN_LINEARLAYOUT_H