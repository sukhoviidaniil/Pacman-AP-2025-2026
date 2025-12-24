/***************************************************************
 * Project:       Pacman
 * File:          SFML_View.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-17
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

#include "view/sfml/SFML_View.h"

#include "infra/diagnostics/Logger.h"

namespace view {
    SFML_View::SFML_View(const infra::ast::View &info, const std::string &texture_dir_path
        ) :
        View(info.type),
        window_(sf::VideoMode(info.window_width, info.window_height), "Pacman")
    {
        sf::View view(sf::FloatRect(0, 0, static_cast<float>(info.window_width), static_cast<float>(info.window_height)));
        window_.setView(view);
        window_.setFramerateLimit(30);

        for (const auto& texture_name : info.textures) {
            sf::Texture texture;
            const std::string path = texture_dir_path + texture_name;
            if (!texture.loadFromFile(path)) {
                const std::string err = "Unable to load textures;\n";
                LOG(err);
                throw std::runtime_error(err);
            }
            textures_[texture_name] = std::move(texture);
        }
        for (const auto& sprite : info.sprites) {
            sprite.accept(*this);
        }
        for (const auto& c_sprite : info. complex_sprites) {
            c_sprite.accept(*this);
        }
    }

    void SFML_View::render(const infra::ui::RenderFrameGraph& graph) {
        if (window_.isOpen()) {
            window_.display();
            for (const auto& frame : graph.temp_frames) {
                render(frame);
            }
        }
    }

    void SFML_View::render(const infra::ui::RenderFrame &frame) {
        for (auto& item : frame.items) {
            infra::ui::Rect r = item.rect;

            if (item.space == infra::ui::Space::World) {
                r.p.x = (r.p.x - frame.camera.position.x) * frame.camera.zoom;
                r.p.y = (r.p.y - frame.camera.position.y) * frame.camera.zoom;
                r.v.x *= frame.camera.zoom;
                r.v.y *= frame.camera.zoom;
            }

            switch (item.type) {
                case infra::ui::ItemType::ComplexSprite : {
                    render_ComplexSprite(item);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void SFML_View::render_ComplexSprite(const infra::ui::RenderItem &item) {
        auto it = complex_sprites_.find(item.sprite);
        if (it == complex_sprites_.end()) {
            throw std::invalid_argument("No complex sprite found for " + item.sprite);
        }
        SFML_Complex_Sprite& cs = *it->second;
        if (item.status.has_value() && item.direction.has_value()) {

            sf::Sprite& sprite = cs.sprite(item.status.value(), item.direction.value());

            sf::Vector2f targetSize{
                item.rect.v.x,
                item.rect.v.y
            };
            auto bounds = sprite.getLocalBounds();

            sprite.setScale(
                targetSize.x / bounds.width,
                targetSize.y / bounds.height
            );
            sprite.setPosition(item.rect.p.x, item.rect.p.y);
            window_.draw(sprite);
        }
    }


}
