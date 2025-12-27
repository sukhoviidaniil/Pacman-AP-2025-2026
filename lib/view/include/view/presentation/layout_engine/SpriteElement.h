/***************************************************************
 * Project:       Pacman
 * File:          SpriteElement.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-27
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
#ifndef PACMAN_UI_SPRITEELEMENT_H
#define PACMAN_UI_SPRITEELEMENT_H
#include <utility>

#include "UIElement.h"
#include "view/presentation/render/RI_Sprite.h"

namespace view::ui {

    class SpriteElement : public UIElement {
    public:
        explicit SpriteElement(std::string  sprite, float sprite_width, float sprite_height)
            : sprite_(std::move(sprite)) {
            width.value = sprite_width;
            height.value = sprite_height;
        }


        infra::math::Vector2 measure(const infra::math::Vector2& available) override {
            infra::math::Vector2 size{
                std::max(0.f, available.x),
                std::max(0.f, available.y)
            };

            size.x = resolve(width, available.x);
            size.y = resolve(height, available.y);

            size.x = std::clamp(size.x, min_size.x, max_size.x);
            size.y = std::clamp(size.y, min_size.y, max_size.y);

            return size;
        }

        void append_render_items(RenderFrame& frame, const ViewContext& /*ctx*/) const override {
            if (!visible) return;

            auto item = std::make_unique<RI_Sprite>();
            item->sprite = sprite_;
            item->rect = result.rect;
            frame.constant_items.push_back(std::move(item));
        }

    private:
        static float resolve(const infra::ui::Size& s, float avail) {
            switch (s.type) {
                case infra::ui::Size::Type::Pixel:   return s.value;
                case infra::ui::Size::Type::Percent: return avail * s.value;
                default:                             return avail;
            }
        }

    std::string sprite_;
    };
}

#endif //PACMAN_UI_SPRITEELEMENT_H