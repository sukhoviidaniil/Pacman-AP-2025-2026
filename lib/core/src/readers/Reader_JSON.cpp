/***************************************************************
 * Project:       Pacman
 * File:          Reader_JSON.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-26
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

#include "core/readers/Reader_JSON.h"

#include <fstream>

#include "core/info/Status_Info.h"
// #include "func_open_file.h"

namespace Core {
    nlohmann::json Reader_JSON::get_json_data(const std::string &filename) {
        std::ifstream file;  //open_file(filename); TODO ADD OPEN FILE
        nlohmann::json data;
        file >> data;
        file.close();
        return data;
    }

    Reader_JSON::Reader_JSON() = default;

    Reader_JSON::~Reader_JSON() = default;

    void Reader_JSON::load_SFML_Sprite(Graphics::SFML_Manager &manager, const std::string &filename) const {
        throw;
    }

    void Reader_JSON::load_SFML_Sprite_Group(Graphics::SFML_Manager &manager, const std::string &filename) const {

        nlohmann::json data = get_json_data(filename);

        auto using_texture = data["using_texture"].get<std::string>();

        const auto texOpt = manager.get_Texture(using_texture);
        if (!texOpt) {
            throw std::invalid_argument("Missing texture");
        }
        const sf::Texture& texture = texOpt->get();

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

                const auto s = data["statuses"][i].get<Info::Status_Info>();

                for (unsigned int top_index = 0; top_index < s.facial_expressions.size(); ++top_index) {
                    const Info::Expression_Info& expression = s.facial_expressions[top_index];
                    const Math::Vector2 direction = expression.direction;
                    int recLeft = expression.recLeft;
                    int recTop = expression.recTop;

                    // If it is negative, it means that such a parameter was not found.
                    if (recLeft < 0) {
                        // left_index = move left
                        const int base = static_cast<int>(s.recLeft.base);
                        const  int increase = static_cast<int>(s.recLeft.increase);
                        recLeft = base + increase * left_index;
                    }
                    // If it is negative, it means that such a parameter was not found.
                    if (recTop < 0) {
                        // facial_expression = move down
                        const int base = static_cast<int>(s.recTop.base);
                        const int increase = static_cast<int>(s.recTop.increase);
                        recTop = base + increase * static_cast<int>(top_index);
                    }

                    const sf::IntRect rect(recLeft, recTop, sprite_width, sprite_height);
                    sf::Sprite sprite(texture, rect);
                    sprite.setOrigin(static_cast<float>(rect.width) / 2.f, static_cast<float>(rect.height) / 2.f);

                    entity_sprites[i][direction].push_back(sprite);
                }
            }

            manager.add_Sprite_Group(name, std::make_shared<Graphics::Sprite_Group>(entity_sprites));
            left_index++;
        }
    }

    std::shared_ptr<Graphics::Camera> Reader_JSON::make_Camera(const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);
        const unsigned int width = data["width"].get<unsigned int>();
        const unsigned int height = data["height"].get<unsigned int>();
        const float window_center_x = data["window_center_x"].get<float>();
        const float window_center_y = data["window_center_y"].get<float>();
        const float logic_center_x = data["logic_center_x"].get<float>();
        const float logic_center_y = data["logic_center_y"].get<float>();
        return std::make_shared<Graphics::Camera>(width, height, Math::Vector2(window_center_x, window_center_y), Math::Vector2(logic_center_x, logic_center_y));
    }

    std::shared_ptr<Logic::Tile_Grid> Reader_JSON::make_Tile_Grid(std::shared_ptr<::Info::Validation> &info,
        std::shared_ptr<Stage> &stage, const Graphics::SFML_Manager &manage, const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);
        const unsigned int width = data["width"].get<unsigned int>();
        const unsigned int height = data["height"].get<unsigned int>();
        const float tile_size = data["height"].get<float>();
        const std::vector<std::vector<int>> grid = data["grid"].get<std::vector<std::vector<int>>>();
    }

    std::shared_ptr<Stage> Reader_JSON::make_Stage(std::shared_ptr<::Info::Validation> &info,
        const std::shared_ptr<File_Reader> &fr, const Graphics::SFML_Manager &manage,
        const std::string &filename) const {
    }

    Stage_Manager Reader_JSON::make_Stage_Manager(const std::shared_ptr<File_Reader> &fr,
        const Graphics::SFML_Manager &manage, const std::string &path) {
    }

}
