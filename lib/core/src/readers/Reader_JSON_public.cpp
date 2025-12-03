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

#include "core/File_Reader.h"
#include "core/info/Status_Info.h"
#include "graphics/Graphics_Factory.h"
#include "logic/Logic_Factory.h"
#include "graphics/view/Actor_View.h"

namespace Core {

    Reader_JSON::Reader_JSON() = default;

    Reader_JSON::~Reader_JSON() = default;

    void Reader_JSON::load_SFML_Sprite(
        const std::shared_ptr<Graphics::SFML_Manager>& sfml_manager, const std::string &filename
        ) const {
        nlohmann::json data = get_json_data(filename);
        auto using_texture = data["using_texture"].get<std::string>();
        const auto texOpt = sfml_manager->get_Texture(using_texture);
        if (!texOpt) {
            throw std::invalid_argument("Missing texture");
        }
        const sf::Texture& texture = texOpt->get();
        const auto sprite = std::make_shared<sf::Sprite>(texture);
        const auto name = data["name"].get<std::string>();
        sfml_manager->add_Sprite(name, sprite);
        throw;
    }

    void Reader_JSON::load_SFML_Sprite_Group(
        const std::shared_ptr<Graphics::SFML_Manager>& sfml_manager, const std::string &filename
        ) const {

        nlohmann::json data = get_json_data(filename);

        auto using_texture = data["using_texture"].get<std::string>();

        const auto texOpt = sfml_manager->get_Texture(using_texture);
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

            sfml_manager->add_Sprite_Group(name, std::make_shared<Graphics::Sprite_Group>(entity_sprites));
            left_index++;
        }
    }

    std::shared_ptr<Graphics::SFML_Manager> Reader_JSON::load_SFML_Manager(
        const std::shared_ptr<const File_Reader> &fr, const std::string &filename
        ) const {
        nlohmann::json data = get_json_data(filename);
        std::shared_ptr<Graphics::SFML_Manager> manager;
        if (!data.contains("textures")) {
            throw std::invalid_argument("Missing textures");
        }
        for (const auto& name : data["textures"]) {
            fr->load_SFML_texture(manager, name);
        }
        if (data.contains("sprites")) {
            for (const auto& name : data["sprites"]) {
                fr->load_SFML_Sprite(manager, name);
            }
        }
        if (!data.contains("sprite_groups")) {
            throw std::invalid_argument("Missing sprite_groups");
        }
        for (const auto& name : data["sprite_groups"]) {
            fr->load_SFML_Sprite_Group(manager, name);
        }
        return manager;
    }

    std::shared_ptr<Logic::Collision::HitBoxe> Reader_JSON::load_HitBoxe(const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);

        Logic::Collision::HitBoxe_Shape_Info info;
        if (data.contains("position")) {
            info.pos = from_json(data["position"]);
        }
        if (data.contains("width")) {
            info.width = data["width"].get<float>();
        }
        if (data.contains("height")) {
            info.height = data["height"].get<float>();
        }
        if (data.contains("layer")) {
            info.layer= data["layer"].get<unsigned int>();
        }
        if (data.contains("height")) {
           info.strength = data["strength"].get<unsigned int>();
        }
        return Logic::Logic_Factory::make_HitBox(info);
    }

    std::shared_ptr<Graphics::Camera> Reader_JSON::load_Camera(const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);
        unsigned int width = 0;
        unsigned int height = 0;
        if (data.contains("width")) {
            width = data["width"].get<unsigned int>();
        }
        if (data.contains("height")) {
           height = data["height"].get<unsigned int>();
        }
        float window_center_x = 0;
        float window_center_y = 0;
        float logic_center_x = 0;
        float logic_center_y = 0;
        if (data.contains("window_center_x")) {
            window_center_x = data["window_center_x"].get<float>();
        }
        if (data.contains("window_center_y")) {
            window_center_y = data["window_center_y"].get<float>();
        }
        if (data.contains("logic_center_x")) {
            logic_center_x = data["logic_center_x"].get<float>();
        }
        if (data.contains("logic_center_y")) {
            logic_center_y = data["logic_center_y"].get<float>();
        }
        return std::make_shared<Graphics::Camera>(width, height, Math::Vector2(window_center_x, window_center_y), Math::Vector2(logic_center_x, logic_center_y));
    }

    void Reader_JSON::load_Entities(
        const std::shared_ptr<const File_Reader> &fr,
        std::shared_ptr<World> &world,
        const std::string &filename) const {

        nlohmann::json data = get_json_data(filename);
        if (!data.contains("entities")) {
            throw std::invalid_argument("File does not contain entities");
        }

        for (const auto& entity : data["entities"]) {
            Entity_JSON_Info info(fr, entity, world);
            add_Entity(info);
        }
    }

    std::shared_ptr<Logic::Tile_Grid> Reader_JSON::load_Tile_Grid(
        std::shared_ptr<Stage> &stage,
        const std::string &filename) const {

        nlohmann::json data = get_json_data(filename);

        unsigned int width = 0;
        unsigned int height = 0;
        if (data.contains("width")) {
            width = data["width"].get<unsigned int>();
        }else {
            // TODO
            // info->add(Info::Error("The camera configuration " + filename+ " does not have a width parameter;"));
        }
        if (data.contains("height")) {
            height = data["height"].get<unsigned int>();
        }else {
            // TODO
            // info->add(Info::Error("The camera configuration " + filename+ " does not have a height parameter;"));
        }

        float tile_size = 1.0f;
        std::vector<std::vector<int>> grid;
        if (data.contains("tile_size")) {
            tile_size = data["tile_size"].get<float>();
        }else {
            // TODO
            // info->add(Info::Error("The camera configuration " + filename+ " does not have a tile_size parameter;"));
        }
        if (data.contains("grid")) {
            grid = data["grid"].get<std::vector<std::vector<int>>>();
        }else {
            // TODO
            // info->add(Info::Error("The camera configuration " + filename+ " does not have a grid parameter;"));
        }

        throw;
        // TODO;
    }

    std::shared_ptr<Stage> Reader_JSON::load_Stage(
        const std::shared_ptr<const File_Reader> &fr,
        const std::string &filename
        ) const {

    }

    Stage_Manager Reader_JSON::load_Stage_Manager(
        const std::shared_ptr<const File_Reader> &fr,
        const std::string &path
        ) const {
        Stage_Manager sm = Stage_Manager(fr);
        nlohmann::json data = get_json_data(path);
        if (!data.contains("stages")) {
            throw std::invalid_argument("File does not contain stages");
        }
        for (const auto& stage : data["stages"]) {
            std::unique_ptr<Stage_Info> info;
            info->type = stage["type"].get<std::string>();
            info->name = stage["name"].get<std::string>();
            info->configuration = stage["configuration"].get<std::string>();
            sm.add_Stage_Info(std::move(info));
        }
        if (!data.contains("start_stage")) {
            throw std::invalid_argument("File does not contain stages");
        }
        const std::string start_stage = data["sstart_stage"].get<std::string>();
        sm.push_stage(start_stage);
        return sm;
    }

    Info::Game_Info Reader_JSON::get_Game_Info(const std::string &filename) {
        nlohmann::json data = get_json_data(filename);
        Info::Game_Info info;
        if (data.contains("graphics")) {
            info.graphics = data["graphics"].get<std::string>();
        }
        if (data.contains("window_width")) {
            info.window_width = data["window_width"].get<unsigned int>();
        }
        if (data.contains("window_height")) {
            info.window_width = data["window_height"].get<unsigned int>();
        }
        if (data.contains("graphics_conf")) {
            info.graphics_conf = data["graphics_conf"].get<std::string>();
        }
        if (data.contains("stage_mng")) {
            info.stage_mng = data["stage_mng"].get<std::string>();
        }
        return info;
    }
}
