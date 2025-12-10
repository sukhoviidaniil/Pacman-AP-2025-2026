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
            // key - status of Sprite;
            std::vector<
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
        auto sfml_manager = std::make_shared<Graphics::SFML_Manager>();
        if (!data.contains("textures")) {
            throw std::invalid_argument("Missing textures");
        }
        for (const auto& texture : data["textures"]) {
            std::string texture_name = texture.get<std::string>();
            sf::Texture t = fr->load_SFML_texture(sfml_manager, texture_name);
        }

        if (data.contains("sprites")) {
            for (const auto& sprite : data["sprites"]) {
                std::string sprite_name = sprite.get<std::string>();
                fr->load_SFML_Sprite(sfml_manager, sprite_name);
            }
        }

        if (data.contains("sprite_groups")) {
            for (const auto& sprite : data["sprite_groups"]) {
                std::string sprite_name = sprite.get<std::string>();
                fr->load_SFML_Sprite_Group(sfml_manager, sprite_name);
            }
        }

        return sfml_manager;
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
        if (data.contains("strength")) {
           info.strength = data["strength"].get<unsigned int>();
        }
        return Logic::Logic_Factory::make_HitBox(info);
    }

    std::shared_ptr<Graphics::Camera> Reader_JSON::load_Camera(const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);

        unsigned int base_window_width = 0;
        unsigned int base_window_height = 0;
        Math::Vector2 window_center;
        if (data.contains("base_window_width")) {
            base_window_width = data["base_window_width"].get<unsigned int>();
        }
        if (data.contains("base_window_height")) {
           base_window_height = data["base_window_height"].get<unsigned int>();
        }
        if (data.contains("window_center")) {
            window_center = from_json(data["window_center"]);
        }

        unsigned int camera_width = 0;
        unsigned int camera_height = 0;
        Math::Vector2 camera_center;
        if (data.contains("camera_width")) {
            camera_width = data["camera_width"].get<unsigned int>();
        }
        if (data.contains("camera_height")) {
            camera_height = data["camera_height"].get<unsigned int>();
        }
        if (data.contains("camera_center")) {
            camera_center = from_json(data["camera_center"]);
        }

        return std::make_shared<Graphics::Camera>(base_window_width, base_window_height, window_center, camera_width, camera_height, camera_center);
    }

    void Reader_JSON::load_Entities(
        const std::shared_ptr<const File_Reader> &fr,
        const std::shared_ptr<Stage> &stage,
        const std::string &filename) const {

        nlohmann::json data = get_json_data(filename);
        if (!data.contains("entities")) {
            throw std::invalid_argument("File does not contain entities");
        }

        for (const auto& entity : data["entities"]) {
            Stage_Info_JSON conf(fr, stage, entity);
            load_Entity(conf);
        }
    }

    void Reader_JSON::load_Entities(
        const std::shared_ptr<const File_Reader> &fr,
        const std::shared_ptr<Stage> &stage,
        const std::shared_ptr<Logic::Tile_Grid> &grid,
        const std::string &filename) const {

        nlohmann::json data = get_json_data(filename);
        if (!data.contains("entities")) {
            throw std::invalid_argument("File does not contain entities");
        }

        for (const auto& entity : data["entities"]) {
            Stage_Info_JSON conf(fr, stage, entity);
            load_Entity(conf, grid);
        }

    }

    Graphics::Tile_Grid_Pair Reader_JSON::load_Tile_Grid(
        std::shared_ptr<Graphics::SFML_Manager> sfml_manager,
        const std::string &filename) const {

        nlohmann::json data = get_json_data(filename);

        if (!data.contains("rows")) {
            throw std::invalid_argument("The camera configuration " + filename+ " does not have a rows parameter;");
        }
        if (!data.contains("columns")) {
            throw std::invalid_argument("The camera configuration " + filename+ " does not have a columns parameter;");
        }
        if (!data.contains("tile_size")) {
            throw std::invalid_argument("The camera configuration " + filename+ " does not have a tile_size parameter;");
        }
        if (!data.contains("grid")) {
            throw std::invalid_argument("The camera configuration " + filename+ " does not have a grid parameter;");
        }

        Logic::Tile_Grid_Info info;
        info.rows = data["rows"].get<unsigned int>();
        info.columns = data["columns"].get<unsigned int>();
        info.tile_size = data["tile_size"].get<float>();
        info.logic_grid = data["grid"].get<std::vector<std::vector<int>>>();

        return Graphics::Graphics_Factory::make_Tile_Grid(sfml_manager, info);
    }

    std::shared_ptr<Stage> Reader_JSON::load_Stage(
        const std::shared_ptr<const File_Reader> &fr,
        const std::string &path
        ) const {
        nlohmann::json data = get_json_data(path);
        if (!data.contains("Type")) {
            throw std::runtime_error("Stage dont have Type");
        }
        const auto entity_type = data["Type"].get<std::string>();

        std::unordered_map<std::string, std::shared_ptr<Stage>(Reader_JSON::*)(const Reader_Base_Info_JSON &conf) const> functionMap;
        Stage_Register(functionMap);
        auto it = functionMap.find(entity_type);
        if (it != functionMap.end()) {
            Reader_Base_Info_JSON conf(fr, data);
            auto memberFn = it->second;
            return (this->*memberFn)(conf);
        }
        throw std::runtime_error("Stage type " + entity_type + " not found");
    }

    Stage_Manager Reader_JSON::load_Stage_Manager(
        const std::shared_ptr<const File_Reader> &fr,
        const std::string &path
        ) const {
        nlohmann::json data = get_json_data(path);
        if (!data.contains("stages")) {
            throw std::invalid_argument("File does not contain stages");
        }
        if (!data.contains("start_stage")) {
            throw std::invalid_argument("File does not contain stages");
        }

        Stage_Manager sm = Stage_Manager(fr);

        for (const auto& stage : data["stages"]) {
            auto info = std::make_unique<Stage_Info>();
            info->name = stage["name"].get<std::string>();
            info->configuration = stage["configuration"].get<std::string>();
            sm.add_Stage_Info(std::move(info));
        }
        const std::string start_stage = data["start_stage"].get<std::string>();
        sm.push_stage(start_stage);
        return sm;
    }

    Info::Game_Info Reader_JSON::get_Game_Info(const std::string &filename) {
        nlohmann::json data = get_json_data(filename);
        Info::Game_Info info;
        if (!data.contains("graphics")) {
            throw std::invalid_argument("File does not contain graphics");
        }
        if (!data.contains("window_width")) {
            throw std::invalid_argument("File does not contain window_width");
        }
        if (!data.contains("window_height")) {
            throw std::invalid_argument("File does not contain window_height");
        }
        if (!data.contains("graphics_conf")) {
            throw std::invalid_argument("File does not contain graphics_conf");
        }
        if (!data.contains("stage_mng")) {
            throw std::invalid_argument("File does not contain stage_mng");
        }
        info.graphics = data["graphics"].get<std::string>();
        info.window_width = data["window_width"].get<unsigned int>();
        info.window_height = data["window_height"].get<unsigned int>();
        info.graphics_conf = data["graphics_conf"].get<std::string>();
        info.stage_mng = data["stage_mng"].get<std::string>();
        return info;
    }
}
