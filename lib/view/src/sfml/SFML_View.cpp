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


    void SFML_View::render(const view::ui::RenderFrame &frame) {
        window_.clear();
        for (auto& item : frame.constant_items) {
            item->accept(*this);
        }
        for (auto& item : frame.temp_items) {
            item->accept(*this);
        }
        window_.display();
    }
}
