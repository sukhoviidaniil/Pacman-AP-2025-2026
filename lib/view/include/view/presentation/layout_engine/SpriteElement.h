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
#include "UIElement.h"
#include "view/presentation/render/RI_Sprite.h"

namespace view::ui {

    class SpriteElement : public UIElement {
    public:
        explicit SpriteElement(const std::string& sprite, float sprite_width, float sprite_height)
            : sprite_(sprite), sprite_width_(sprite_width), sprite_height_(sprite_height)
        {}

        // Измеряем размер спрайта
        infra::math::Vector2 measure(const infra::math::Vector2& available) override {
            infra::math::Vector2 size{
                std::max(0.f, available.x),
                std::max(0.f, available.y)
            };

            if (width.type != infra::ui::Size::Type::Auto)
                size.x = resolve(width, available.x);
            else
                size.x = sprite_width_;

            if (height.type != infra::ui::Size::Type::Auto)
                size.y = resolve(height, available.y);
            else
                size.y = sprite_height_;

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
    float sprite_width_;
    float sprite_height_;
    };
}

#endif //PACMAN_UI_SPRITEELEMENT_H