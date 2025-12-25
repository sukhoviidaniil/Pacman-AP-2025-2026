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

#include "view/presentation/layout_engine/UIElement.h"
#include "infra/math/Vector2.h"
#include "infra/presentation/external/Alignment.h"
#include "infra/presentation/external/Rect.h"

namespace view::ui {

    /**
     * @brief Base class for linear layout containers.
     *
     * Arranges child elements in a single row or column, optionally
     * supporting alignment, spacing, and flexible growth.
     */
    class LinearLayout : public UIElement {
    public:
        /// @brief Alignment of children along the cross axis.
        infra::ui::Align align = infra::ui::Align::Start;
        /// @brief Spacing between consecutive children.
        float spacing = 0.f;

    protected:
        /**
         * @brief Determines if the layout is horizontal or vertical.
         *
         * Must be implemented by derived classes.
         *
         * @return true if horizontal, false if vertical.
         */
        [[nodiscard]] virtual bool horizontal() const = 0;

        /**
         * @brief Measures the desired size of the layout.
         *
         * Accumulates the sizes of visible children along the main axis
         * and takes the maximum along the cross axis. Spacing between
         * children is included in the measurement.
         *
         * @param available Available space from the parent.
         * @return Desired size of the layout.
         */
        infra::math::Vector2 measure(const infra::math::Vector2 &available) override {
            infra::math::Vector2 total{0.f, 0.f};
            size_t visible_count = 0;

            for (auto& c : children) {
                if (!c->visible) continue;

                infra::math::Vector2 cs = c->measure(available);
                ++visible_count;

                if (horizontal()) {
                    total.x += cs.x;
                    total.y = std::max(total.y, cs.y);
                } else {
                    total.y += cs.y;
                    total.x = std::max(total.x, cs.x);
                }
            }

            if (visible_count > 1) {
                if (horizontal()) total.x += spacing * static_cast<float>(visible_count - 1);
                else              total.y += spacing * static_cast<float>(visible_count - 1);
            }

            return total;
        }

        /**
         * @brief Lays out children within the assigned rectangle.
         *
         * Calculates positions and sizes for each child, taking into
         * account fixed and flexible elements, alignment, and spacing.
         *
         * @param r Final rectangle assigned by the parent layout.
         */
        void layout(infra::ui::Rect r) override {
             result.rect = r;

            infra::math::Point2 p{r.x, r.y};
            infra::math::Vector2 v{r.width, r.height};

            const float main  = horizontal() ? v.x : v.y;
            const float cross = horizontal() ? v.y : v.x;

            float fixed = 0.f;
            float flex_sum = 0.f;
            size_t visible_count = 0;

            for (auto& c : children) {
                if (!c->visible) continue;

                ++visible_count;

                if (c->flex > 0.f) {
                    flex_sum += c->flex;
                } else {
                    infra::math::Vector2 s = c->measure(v);
                    fixed += horizontal() ? s.x : s.y;
                }
            }

            const float free = std::max(
                0.f,
                main - fixed - spacing * static_cast<float>(visible_count > 0 ? visible_count - 1 : 0)
            );

            float cursor = horizontal() ? p.x : p.y;

            for (auto& c : children) {
                if (!c->visible) continue;

                infra::math::Vector2 s = c->measure(v);

                float main_size =
                    (c->flex > 0.f && flex_sum > 0.f)
                        ? free * (c->flex / flex_sum)
                        : (horizontal() ? s.x : s.y);

                float cross_size =
                    align == infra::ui::Align::Stretch
                        ? cross
                        : (horizontal() ? s.y : s.x);

                float cross_pos = horizontal() ? p.y : p.x;

                if (align != infra::ui::Align::Stretch) {
                    const float extra = cross - cross_size;
                    if (align == infra::ui::Align::Center) cross_pos += extra * 0.5f;
                    else if (align == infra::ui::Align::End) cross_pos += extra;
                }

                infra::ui::Rect cr;

                if (horizontal()) {
                    cr = {cursor, cross_pos, main_size, cross_size};
                } else {
                    cr = {cross_pos, cursor, cross_size, main_size};
                }

                c->layout(cr);
                cursor += main_size + spacing;
            }
        }
    };
}
#endif //PACMAN_LINEARLAYOUT_H