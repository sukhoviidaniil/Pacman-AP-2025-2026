/***************************************************************
 * Project:       Pacman
 * File:          UIElement.h
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
#ifndef PACMAN_UIELEMENT_H
#define PACMAN_UIELEMENT_H


#include "Base.h"
#include "LayoutResult.h"
#include "Size.h"


namespace infra::ui {
    class UIElement {
    public:
        virtual ~UIElement() = default;

        void add(std::shared_ptr<UIElement> child) {
            children.push_back(std::move(child));
        }

        // ===== Layout API =====
        virtual Vec2 measure(Vec2 available) {
            return resolve_size(available);
        }

        virtual void layout(Rect r) {
            result.rect = r;
            for (auto& c : children)
                c->layout(r);
        }

        // ===== Configuration =====
        Size width  = Size::auto_();
        Size height = Size::auto_();

        Vec2 min_size {0, 0};
        Vec2 max_size {1e9f, 1e9f};

        Vec2 margin  {0, 0};
        Vec2 padding {0, 0};

        float flex = 0.f; // 0 = fixed, >0 = flex grow

        bool visible = true;

        LayoutResult result;

    protected:
        std::vector<std::shared_ptr<UIElement>> children;

        Vec2 resolve_size(Vec2 available) {
            Vec2 out;

            auto resolve = [&](Size s, float avail) {
                if (s.type == Size::Type::Pixel)   return s.value;
                if (s.type == Size::Type::Percent) return avail * s.value;
                return avail; // Auto
            };

            out.x = resolve(width,  available.x);
            out.y = resolve(height, available.y);

            out.x = std::clamp(out.x, min_size.x, max_size.x);
            out.y = std::clamp(out.y, min_size.y, max_size.y);

            return out;
        }
    };
}

#endif //PACMAN_UIELEMENT_H