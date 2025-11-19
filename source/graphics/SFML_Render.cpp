/***************************************************************
 * Project:       Pacman
 * File:          SFML_Render.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-09
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

#include "graphics/SFML_Render.h"

#include "../../include/graphics/info/Status_Info.h"
#include "func/func_get_json_data.h"

#include <utility>

namespace Graphics {

    sf::Texture& SFML_Render::find_texture(const std::string &name) {
        sf::Texture* texturePtr = nullptr;
        const auto it = textures_.find(name);
        if (it != textures_.end()) {
            texturePtr = &it->second;
        }else {
            texturePtr = &load_texture(name);
        }
        sf::Texture& texture = *texturePtr;
        return texture;
    }

    SFML_Render::SFML_Render(std::string texture_folder, std::string configuration_folder):
    texture_folder_(std::move(texture_folder)), configuration_folder_(std::move(configuration_folder)){
    }

    sf::Texture& SFML_Render::load_texture(const std::string &filename) {
        auto it = textures_.find(filename);
        if (it != textures_.end())
            return it->second; // texture already loaded

        // Create a texture directly in the container
        auto& tex = textures_[filename];
        if (!tex.loadFromFile(texture_folder_ + filename))
            throw std::runtime_error("Texture loading error");
        return tex;
    }

    void SFML_Render::load_Sprite(const std::string &filename) {
    }

    void SFML_Render::load_Sprite_Group(const std::string &filename) {
        std::string full_filename = configuration_folder_ + filename;
        nlohmann::json data = get_json_data(full_filename);

        auto from_file = data["from_file"].get<std::string>();

        sf::Texture& texture = find_texture(from_file);

        auto names = data["names"].get<std::vector<std::string>>();
        int left_index = 0;
        for (const std::string& name : names) {


            std::vector<
                // key - status of Sprite;
                std::unordered_map<
                    // key - direction of Sprite;
                    Math::Vector2,
                    // animation
                    std::vector<
                        sf::Sprite
                    >,
                    // custom hash function
                    Math::Vector2Hash
                >
            > entity_sprites;

            const int sprite_width = data["sprite_width"].get<int>();
            const int sprite_height = data["sprite_height"].get<int>();
            const auto number_of_statuses = data["number_of_statuses"].get<unsigned int>();
            entity_sprites.resize(number_of_statuses);

            for (unsigned int i = 0; i < number_of_statuses; i++) {
                nlohmann::json status = data["statuses"][i];
                // status = new coordinates

                const Info::Status_Info s = data["statuses"][i].get<Info::Status_Info>();

                for (unsigned int top_index = 0; top_index < s.facial_expressions.size(); ++top_index) {
                    const Info::Expression_Info& expression = s.facial_expressions[top_index];
                    const Math::Vector2 direction = expression.direction;
                    int recLeft = expression.recLeft;
                    int recTop = expression.recTop;

                    // If it is negative, it means that such a parameter was not found.
                    if (recLeft < 0) {
                        // left_index = move left
                        const unsigned int base = s.recLeft.base;
                        const unsigned int increase = s.recLeft.increase;
                        recLeft = base + increase * left_index;
                    }
                    // If it is negative, it means that such a parameter was not found.
                    if (recTop < 0) {
                        // facial_expression = move down
                        const unsigned int base = s.recTop.base;
                        const unsigned int increase = s.recTop.increase;
                        recTop = base + increase * top_index;
                    }

                    const sf::IntRect rect(recLeft, recTop, sprite_width, sprite_height);
                    sf::Sprite sprite(texture, rect);
                    sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);

                    entity_sprites[i][direction].push_back(sprite);
                }
            }
            grouped_sprites_[name] = std::make_shared<Sprite_Group>(entity_sprites);
            left_index++;
        }
    }

    std::shared_ptr<Sprite_Group> SFML_Render::get_Sprite_Group(const std::string &name) {
        auto it = grouped_sprites_.find(name);
        if (it != grouped_sprites_.end())
            return it->second; // already loaded
        throw std::runtime_error("No sprite group named " + name);
    }
}
