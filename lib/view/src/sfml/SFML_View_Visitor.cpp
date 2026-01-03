/***************************************************************
 * Project:       Pacman
 * File:          SFML_View_Visitor.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-24
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

#include "infra/diagnostics/Logger.h"
#include "view/presentation/render/RI_ComplexSprite.h"
#include "view/presentation/render/RI_Label.h"
#include "view/presentation/render/RI_Rectangle.h"
#include "view/presentation/render/RI_Sprite.h"
#include "view/sfml/SFML_Animation.h"
#include "view/sfml/SFML_View.h"

namespace view {
    void SFML_View::visit(const infra::ast::Sprite &i_sprite) {
        const std::string name = i_sprite.name;
        auto it = sprites_.find(name);
        if (it != sprites_.end()) {
            // A minor error.
            std::string err = "The Sprite named " + name + " has already been loaded, configuration Warning.";
            LOG(err);
            return;
        }

        const sf::Texture& texture = get_Texture(i_sprite.using_texture, "infra::ast::Sprite " + name);
        const int sprite_width = static_cast<int>(i_sprite.sprits_width);
        const int sprite_height = static_cast<int>(i_sprite.sprits_height);
        int recLeft = i_sprite.recLeft;
        int recTop = i_sprite.recTop;

        if (recLeft < 0) {
            // A minor error.
            std::string err = "The Sprite named " + name + " recLeft < 0.";
            LOG(err);
            recLeft = 0;
        }
        if (recTop < 0) {
            // A minor error.
            std::string err = "The Sprite named " + name + " recTop < 0.";
            LOG(err);
            recTop = 0;
        }

        const sf::IntRect rect(recLeft, recTop, sprite_width, sprite_height);
        sf::Sprite sprite(texture, rect);
        //sprite.setOrigin(static_cast<float>(rect.width) / 2.f, static_cast<float>(rect.height) / 2.f);

        sprites_[name] = std::move(sprite);
    }

    void SFML_View::visit(const infra::ast::ComplexSprite &complex_sprite) {

        const sf::Texture& texture = get_Texture(complex_sprite.using_texture, "infra::ast::Complex_Sprite");
        int left_index = 0;
        for (const std::string& name : complex_sprite.groups_names) {
            auto it = complex_sprites_.find(name);
            if (it != complex_sprites_.end()) {
                // A minor error.
                std::string err = "The complex splice named " + name + " has already been loaded, configuration error.";
                LOG(err);
                continue;
            }
            std::unordered_map<
                infra::Status,
                std::unordered_map<
                    infra::math::Direction,
                    // animation
                    std::unique_ptr<ISFML_Sprite>,
                    infra::math::DirectionHash
                >
            > data;

            const int sprite_width = static_cast<int>(complex_sprite.sprits_width);
            const int sprite_height = static_cast<int>(complex_sprite.sprits_height);

            for (const auto& group :  complex_sprite.groups_) {

                // status = new coordinates
                const infra::ast::SpriteStatus& status = group.second;
                const auto directions = static_cast<unsigned int>(status.sprite_directions.size());

                for (unsigned int top_index = 0; top_index < directions; ++top_index) {
                    const infra::ast::Sprite_Direction& sprite_direction = status.sprite_directions[top_index];
                    infra::math::Direction direction = sprite_direction.direction;
                    int recLeft = sprite_direction.recLeft;
                    int recTop = sprite_direction.recTop;

                    // If it is negative, it means that such a parameter was not found.
                    if (recLeft < 0) {
                        // left_index = move left
                        const int base = status.recLeft.base;
                        const  int increase = status.recLeft.increase;
                        recLeft = base + increase * left_index;
                    }
                    // If it is negative, it means that such a parameter was not found.
                    if (recTop < 0) {
                        // facial_expression = move down
                        const int base = status.recTop.base;
                        const int increase = status.recTop.increase;
                        recTop = base + increase * static_cast<int>(top_index);
                    }


                    std::unique_ptr<ISFML_Sprite> isprite;
                    if (status.animation.size == 0) {
                        const sf::IntRect rect(recLeft, recTop, sprite_width, sprite_height);
                        sf::Sprite sprite(texture, rect);
                        isprite = std::make_unique<SFML_Sprite>(std::move(sprite));
                    }else {
                        int frame_size = static_cast<int>(status.animation.size);
                        std::vector<sf::Sprite> animations_sprites;
                        for (int index = 0; index < frame_size; ++index) {
                            int left = recLeft;
                            int top = recTop;
                            left +=  index * status.animation.recLeft_increase;
                            top +=  index * status.animation.recTop_increase;
                            const sf::IntRect rect(left, top, sprite_width, sprite_height);
                            sf::Sprite sprite(texture, rect);
                            animations_sprites.push_back(std::move(sprite));
                        }
                        isprite = std::make_unique<SFML_Animation>(frame_size, status.animation.frame_duration, std::move(animations_sprites));
                    }

                    data[group.first][direction] = std::move(isprite);
                }
            }
            complex_sprites_[name] = std::make_unique<SFML_Complex_Sprite>(std::move(data));
            left_index++;
        }
    }

    void SFML_View::render_warning(const infra::ui::Rect& rect) {
        auto it = sprites_.find("Warning");
        if (it == sprites_.end()) {
            ui::RI_Rectangle w;
            w.color = infra::ui::Color{
                0,
                120,
                255,
                255
            };
            w.rect = rect;
            w.accept(*this);
        }else {
            ui::RI_Sprite s;
            s.sprite = "Warning";
            s.rect = rect;
            s.accept(*this);
        }
    }

    void SFML_View::visit(const ui::RI_Label &ri) {
        auto it = fonts_.find(ri.font);
        if (it == fonts_.end()) {
            render_warning(ri.rect);
            return;
        }

        sf::Text text;
        text.setFont(it->second);
        text.setString(ri.text);
        text.setFillColor(sf::Color(
            ri.color.r,
            ri.color.g,
            ri.color.b,
            ri.color.a
        ));
        const auto& r = ri.rect;

        if (ri.size > 0) {
            // Fixed size
            text.setCharacterSize(static_cast<unsigned>(ri.size));
            text.setPosition(r.x, r.y);
        } else {
            // Stretch the text across the entire Rect
            text.setCharacterSize(30); // base size for calculation

            sf::FloatRect bounds = text.getLocalBounds();

            // origin for correct scaling
            text.setOrigin(bounds.left, bounds.top);

            float scaleX = r.width / bounds.width;
            float scaleY = r.height / bounds.height;

            text.setScale(scaleX, scaleY);
            text.setPosition(r.x, r.y);
        }

        window_.draw(text);
    }

    void SFML_View::visit(const ui::RI_Rectangle &ri) {
        sf::RectangleShape rect;

        rect.setPosition(ri.rect.x, ri.rect.y);
        rect.setSize({ ri.rect.width, ri.rect.height });

        rect.setFillColor(
            sf::Color(ri.color.r, ri.color.g, ri.color.b, ri.color.a)
        );

        if (ri.border_width > 0) {
            rect.setOutlineThickness(static_cast<float>(ri.border_width));
            rect.setOutlineColor(
                sf::Color(
                    ri.border_color.r,
                    ri.border_color.g,
                    ri.border_color.b,
                    ri.border_color.a
                )
            );
        } else {
            rect.setOutlineThickness(0.f);
        }
        window_.draw(rect);
    }

    void SFML_View::visit(const ui::RI_Sprite &ri_sprite) {
        auto it = sprites_.find(ri_sprite.sprite);
        if (it == sprites_.end()) {
            render_warning(ri_sprite.rect);
            return;
        }

        sf::Sprite sprite = it->second;

        const auto& r = ri_sprite.rect;
        sprite.setPosition(r.x, r.y);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setScale(
            r.width / bounds.width,
            r.height / bounds.height
        );
        window_.draw(sprite);

    }

    void SFML_View::visit(const ui::RI_ComplexSprite &ri) {
        auto it = complex_sprites_.find(ri.sprite);
        if (it == complex_sprites_.end()) {
            render_warning(ri.rect);
            return;
        }
        sf::Sprite sprite;
        try {
            sprite = it->second->sprite(ri.status, ri.direction);
        } catch (...) {
            throw;
        }


        const auto& r = ri.rect;
        sprite.setPosition(r.x, r.y);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setScale(
            r.width / bounds.width,
            r.height / bounds.height
        );
        window_.draw(sprite);
    }

    void SFML_View::elapsed(float delta) {
        for (auto& it : complex_sprites_) {
            it.second->elapsed(delta);
        }
    }

    const sf::Texture& SFML_View::get_Texture(const std::string& using_texture, const std::string& by_who) {
        if (using_texture.empty()) {
            const std::string err = "The " + by_who +  " texture not specified.";
            LOG(err);
            throw std::invalid_argument(err);
        }
        const auto it = textures_.find(using_texture);
        if (it == textures_.end()) {
            const std::string err = "Missing " + by_who + " texture " + using_texture;
            LOG(err);
            throw std::invalid_argument(err);
        }
        return std::cref(it->second);
    }
}
