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

#include <iostream>

#include "infra/ast/view/View.h"
#include "../../../infra/include/infra/diagnostics/Logger.h"
#include "infra/event/events/window.hpp"
#include "SFML/Graphics/Texture.hpp"

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
            textures_[texture_name] = texture;
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
        }
    }

    void SFML_View::track_local(const std::shared_ptr<infra::event::Event_Bus>& bus) {
    }

    void SFML_View::track_global(const std::shared_ptr<infra::event::Event_Bus>& bus) {
        using namespace infra::event::window;
        // Closing the window
        track(
            bus->subscribe<Closed>(
                [this](const Closed&) {
                    window_.close();
                }
            )
        );
        // Change window size
        track(
            bus->subscribe<Resized>(
                [this](const Resized& e) {
                    sf::View v = window_.getView();
                    v.setSize(static_cast<float>(e.width),
                              static_cast<float>(e.height));
                    v.setCenter(v.getSize() * 0.5f);
                    window_.setView(v);
                }
            )
        );

        // Loss/gain of focus
    }

    bool SFML_View::poll_event(sf::Event &e)  {
        return window_.pollEvent(e);
    }


    std::optional<sf::Texture> SFML_View::get_Texture(const std::string& using_texture) {
        const auto it = textures_.find(using_texture);
        if (it == textures_.end()) return std::nullopt;
        return it->second;
    }

    void SFML_View::visit(const infra::ast::Sprite &sprite) {
        // TODO
    }

    void SFML_View::visit(const infra::ast::Complex_Sprite &complex_sprite) {
        const auto texOpt = get_Texture(complex_sprite.using_texture);
        if (!texOpt.has_value()) {
            throw std::invalid_argument("Missing texture");
        }
        const sf::Texture& texture = texOpt.value();
        int left_index = 0;
        for (const std::string& name : complex_sprite.groups_names) {
            auto it = complex_sprites_.find(name);
            if (it != complex_sprites_.end()) {
                // A minor error.
                std::string err = "The complex splice named " + name + " has already been loaded, configuration error.";
                LOG(err);
                continue;
            }
            // key - status of Sprite;
            std::vector<
                std::unordered_map<
                    // key - direction of Sprite;
                    infra::math::Vector2,
                    // animation
                    std::vector<
                        sf::Sprite
                    >,
                    // custom hash function
                    infra::math::Vector2Hash
                >
            > data;

            const int sprite_width = static_cast<int>(complex_sprite.sprits_width);
            const int sprite_height = static_cast<int>(complex_sprite.sprits_height);
            const unsigned number_of_statuses = complex_sprite.number_of_statuses;
            data.resize(number_of_statuses);

            for (unsigned int i = 0; i < number_of_statuses; i++) {
                // status = new coordinates
                const infra::ast::Sprite_Status& status = complex_sprite.sprite_statuses[i];
                const auto facial_expressions = static_cast<unsigned int>(status.facial_expressions.size());
                for (unsigned int top_index = 0; top_index < facial_expressions; ++top_index) {
                    const infra::ast::Sprite_Expression& sprite_expression = status.facial_expressions[top_index];

                    infra::math::Vector2 direction = sprite_expression.direction;

                    int recLeft = sprite_expression.recLeft;
                    int recTop = sprite_expression.recTop;
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

                    const sf::IntRect rect(recLeft, recTop, sprite_width, sprite_height);
                    sf::Sprite sprite(texture, rect);
                    sprite.setOrigin(static_cast<float>(rect.width) / 2.f, static_cast<float>(rect.height) / 2.f);
                    data[i][direction].push_back(sprite);
                }
            }
            complex_sprites_[name] = std::make_unique<SFML_Complex_Sprite>(data);
            left_index++;
        }
    }
}
