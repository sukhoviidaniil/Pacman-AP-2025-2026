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


#include "infra/File_Reader.h"
#include "infra/ast/sprite/Sprite_Status.h"
#include "infra/readers/from_JSON.h"
#include "infra/readers/Reader_JSON.h"

namespace infra {

    Reader_JSON::Reader_JSON() = default;

    Reader_JSON::~Reader_JSON() = default;

    ast::Sprite Reader_JSON::read_Sprite(const std::string &filename) const {
        ast::Sprite sprite;
        // TODO
        return sprite;
    }

    ast::Sprits_Group Reader_JSON::read_Sprits_Group(const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);
        ast::Sprits_Group sg;
        sg.using_texture = get_checked<std::string>("using_texture", data, filename);
        sg.sprits_width = get_checked<unsigned int>("sprits_width", data, filename);
        sg.sprits_height = get_checked<unsigned int>("sprits_height", data, filename);
        sg.groups_names = get_checked<std::vector<std::string>>("groups_names", data, filename);
        sg.number_of_statuses = get_checked<unsigned int>("number_of_statuses", data, filename);

        if (!data["statuses"].is_array() || data["statuses"].size() != sg.number_of_statuses) {
            throw std::invalid_argument("Sprits_Group parameter statuses is not a list or its size is not equal to the parameter number_of_statuses");
        }
        sg.statuses = get_checked<std::vector<ast::Sprite_Status>>("statuses", data, filename);
        return sg;
    }

    ast::View Reader_JSON::read_View(
        const std::string &filename,
        const std::shared_ptr<const File_Reader> &fr) const {
        nlohmann::json data = get_json_data(filename);
        ast::View vs;

        vs.type = get_checked<std::string>("type", data, filename);
        if (data.contains("textures")) {
            vs.textures = get_checked<std::vector<std::string>>("textures", data, filename);
        }
        if (data.contains("sprites") && data["sprites"].is_array()) {
            for (const auto &sprite : data["sprites"]) {
                if (sprite.is_object()) {
                    ast::Sprite s = get_checked<ast::Sprite>(sprite, filename, "sprites");
                    vs.sprites.push_back(s);
                    continue;
                }
                if (sprite.is_string()) {
                    ast::Sprite s = fr->read_Sprite(sprite.get<std::string>());
                    vs.sprites.push_back(s);
                    continue;
                }
                throw std::invalid_argument("View_Sprites one of the parameters in the “sprites” list is neither a file name nor an object.");
            }
        }

        if (data.contains("sprite_groups") && data["sprite_groups"].is_array()) {
            for (const auto &sprite : data["sprites"]) {
                if (sprite.is_object()) {
                    vs.sprite_groups.push_back(get_checked<ast::Sprits_Group>(sprite, filename, "sprite_groups"));
                    continue;
                }
                if (sprite.is_string()) {
                    vs.sprite_groups.push_back(fr->read_Sprits_Group(sprite.get<std::string>()));
                    continue;
                }
                throw std::invalid_argument("View_Sprites one of the parameters in the “sprite_groups” list is neither a file name nor an object.");
            }
        }
        return vs;
    }

    ast::Model Reader_JSON::read_Model(const std::string& path) const {
        nlohmann::json data = get_json_data(path);
        return get_checked<ast::Model>(data, path, "ROOT");
    }

    ast::Application Reader_JSON::read_Application(
        const std::string &path,
        const std::shared_ptr<const File_Reader> &fr
        ) const {
        nlohmann::json data = get_json_data(path);
        ast::Application app;
        if (data.contains("view")) {
            if (data["view"].is_object()) {
                app.view = get_checked<ast::View>("view", data, path);
            }else if (data["view"].is_string()) {
                auto view = get_checked<std::string>("view", data, path);
                app.view = fr->read_View(view);
            }else {
                throw std::invalid_argument("The view is neither a string nor an object, configuration reading error.");
            }
        }

        std::string m = "models";
        if (data.contains(m) && data[m].is_array()) {
            for (const auto& model_data: data[m]) {
                if (model_data.is_object()) {
                    auto model = get_checked<ast::Model>(model_data, path, m);
                    app.models.push_back(model);
                    continue;
                }
                if (model_data.is_string()) {
                    auto model_file = get_checked<std::string>(model_data, path, m);
                    ast::Model model = fr->read_Model(model_file);
                    app.models.push_back(model);
                    continue;
                }
                throw std::invalid_argument("The model is neither a string nor an object, configuration reading error");
            }
        }
        return app;
    }

    /*
    void Reader_JSON::load_SFML_Sprite(
        const std::shared_ptr<graphics::SFML_Manager>& sfml_manager, const std::string &filename
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
        const std::shared_ptr<graphics::SFML_Manager>& sfml_manager, const std::string &filename
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
                    math::Vector2,
                    // animation
                    std::vector<
                        sf::Sprite
                    >,
                    // custom hash function
                    math::Vector2Hash
                >
            > entity_sprites;

            const int sprite_width = data["sprite_width"].get<int>();
            const int sprite_height = data["sprite_height"].get<int>();
            const auto number_of_statuses = data["number_of_statuses"].get<unsigned int>();
            entity_sprites.resize(number_of_statuses);

            for (unsigned int i = 0; i < number_of_statuses; i++) {
                nlohmann::json status = data["statuses"][i];
                // status = new coordinates

                const auto s = data["statuses"][i].get<Status_Info>();

                for (unsigned int top_index = 0; top_index < s.facial_expressions.size(); ++top_index) {
                    const Expression_Info& expression = s.facial_expressions[top_index];
                    const math::Vector2 direction = expression.direction;
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

            sfml_manager->add_Sprite_Group(name, std::make_shared<graphics::Sprite_Group>(entity_sprites));
            left_index++;
        }
    }

    std::shared_ptr<graphics::SFML_Manager> Reader_JSON::load_SFML_Manager(
        const std::shared_ptr<const File_Reader> &fr, const std::string &filename
        ) const {
        nlohmann::json data = get_json_data(filename);
        auto sfml_manager = std::make_shared<graphics::SFML_Manager>();
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

    logic::collision::HitBoxe_Info Reader_JSON::load_HitBoxe(const std::string &path) const {
        nlohmann::json data = get_json_data(path);

        logic::collision::HitBoxe_Info hbi;
        hbi.tipe_ = get_checked<std::string>(hbi.tipe_, data, "tipe_", path);
        hbi.layer_ = get_checked<int>(hbi.layer_, data, "layer_", path);
        hbi.strength_ = get_checked<int>(hbi.strength_, data, "strength_", path);
        hbi.width_ = get_checked<int>(hbi.width_, data, "width_", path);
        hbi.height_ = get_checked<int>(hbi.height_, data, "height_", path);
        hbi.radius_ = get_checked<int>(hbi.radius_, data, "radius_", path);
        hbi.center_ = get_checked<math::Vector2>(hbi.center_, data, "center_", path);
        hbi.points_ = get_checked<std::vector<math::Vector2>>(hbi.points_, data, "points_", path);
        return hbi;
    }

    graphics::Camera_Info Reader_JSON::load_Camera(const std::string &path) const {
        nlohmann::json data = get_json_data(path);

        graphics::Camera_Info ci;
        ci.window_width = get_checked<unsigned int>(ci.window_width, data, "window_width", path);
        ci.window_height = get_checked<unsigned int>(ci.window_height, data, "window_height", path);
        ci.window_center = get_checked<math::Vector2>(ci.window_center, data, "window_center", path);
        ci.camera_width = get_checked<unsigned int>(ci.camera_width, data, "camera_width", path);
        ci.camera_height = get_checked<unsigned int>(ci.camera_height, data, "camera_height", path);
        ci.camera_center = get_checked<math::Vector2>(ci.camera_center, data, "camera_center", path);

        return ci;
    }

    void Reader_JSON::load_Entities(
        const std::shared_ptr<const File_Reader> &fr,
        const std::shared_ptr<Stage> &stage,
        const std::shared_ptr<logic::Tile_Grid> &grid,
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

    graphics::Tile_Grid_Pair Reader_JSON::load_Tile_Grid(
        std::shared_ptr<graphics::SFML_Manager> sfml_manager,
        const std::string &path
        ) const {

        const nlohmann::json data = get_json_data(path);
        logic::Tile_Grid_Info info;
        info.rows = get_checked<unsigned int>(data, "rows", path);
        info.columns = get_checked<unsigned int>(data, "columns", path);
        info.tile_size = get_checked<float>(data, "tile_size", path);
        info.logic_grid = get_checked<std::vector<std::vector<int>>>(data, "grid", path);
        return graphics::Graphics_Factory::make_Tile_Grid(sfml_manager, info); // TODO return logic::Tile_Grid_Info
    }

    std::shared_ptr<Stage> Reader_JSON::load_Stage(
        const std::shared_ptr<const File_Reader> &fr,
        const std::string &path
        ) const {
        nlohmann::json data = get_json_data(path);

        const auto entity_type = get_checked<std::string>(data, "Type", path);

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
        auto sm = Stage_Manager(fr);

        for (const auto& stage : data["stages"]) {
            auto info = std::make_unique<Stage_Info>();
            info->name = get_checked<std::string>(info->name, stage, "name", path, "stages");
            info->configuration = get_checked<std::string>(info->configuration, stage, "name", path, "stages");
            sm.add_Stage_Info(std::move(info));
        }
        const auto start_stage = get_checked<std::string>(data, "start_stage", path);
        sm.push_stage(start_stage);
        return sm;
    }

    Game_Info Reader_JSON::get_Game_Info(const std::string& path) {
        const nlohmann::json data = get_json_data(path);
        Game_Info info;
        info.graphics = get_checked<std::string>(info.graphics, data, "graphics", path);
        info.window_width = get_checked<int>(info.window_width, data, "window_width", path);
        info.window_height = get_checked<int>(info.window_height, data, "window_height", path);
        info.graphics_conf = get_checked<std::string>(info.graphics, data, "graphics_conf", path);
        info.stage_mng = get_checked<std::string>(info.graphics, data, "stage_mng", path);
        return info;
    }
    */
}
