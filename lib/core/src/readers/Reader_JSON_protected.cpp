/***************************************************************
 * Project:       Pacman
 * File:          Reader_JSON_protected.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-02
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

#include <fstream>
#include <iostream>

#include "core/readers/Reader_JSON.h"
#include "core/File_Reader.h"
#include "core/stages/Stage_Game.h"
#include "core/stages/World.h"

#include "graphics/Graphics_Factory.h"
#include "logic/Logic_Factory.h"
#include "logic/collision/HitBox_Rectangle.h"
#include "logic/collision/Separating_Axis_Theorem.h"

namespace Core {

    std::shared_ptr<Logic::Model::Entity> Reader_JSON::load_Actor(Stage_Info_JSON& conf, const std::shared_ptr<Logic::Tile_Grid> &grid) const{
        const nlohmann::json &data = conf.data_;
        const auto type = data["Type"].get<std::string>();
        std::string actor_name;
        if (!data.contains("Model")) {
            throw std::runtime_error("Entity dont have Model");
        }
        if (data["Model"].is_object()) {
            nlohmann::json model_data = data["Model"];
            Logic::Model::Actor_Info actor_info;
            actor_info.name = model_data["name"].get<std::string>();
            actor_name = actor_info.name;
            Math::Vector2 temp_p = from_json(model_data["position"]);
            actor_info.position = grid->get_nearest_tile_center(temp_p);
            actor_info.speed = model_data["speed"].get<float>();
            actor_info.max_status = model_data["max_status"].get<unsigned int>();
            const std::string hitbox = model_data["hitbox"].get<std::string>();
            actor_info.hitbox = conf.fr_->make_HitBoxe(hitbox);
            std::shared_ptr<Logic::Model::Entity> model = Logic::Logic_Factory::make_Actor(actor_info);
            conf.stage_->add_Model(type, model);
        }else {
            actor_name = data["Model"].get<std::string>();
        }

        std::shared_ptr<Logic::Model::Entity> actor_model = conf.stage_->get_Model(type, actor_name);
        if (actor_model == nullptr) throw std::runtime_error("Actor model not added");
        return actor_model;
    }

    void Reader_JSON::Entity_Register(std::unordered_map<std::string, std::shared_ptr<Logic::Model::Entity>(Reader_JSON::*)(Stage_Info_JSON &conf, const std::shared_ptr<Logic::Tile_Grid> &grid) const> &outMap) const {
        outMap["Actor"] = &Reader_JSON::load_Actor;
    }

    void Reader_JSON::load_Entity(Stage_Info_JSON &conf, const std::shared_ptr<Logic::Tile_Grid> &grid) const {
        const nlohmann::json &data = conf.data_;
        if (!data.contains("Type")) {
            throw std::runtime_error("Entity dont have Type");
        }
        const std::string entity_type = data["Type"].get<std::string>();

        std::unordered_map<std::string, std::shared_ptr<Logic::Model::Entity>(Reader_JSON::*)(Stage_Info_JSON &conf, const std::shared_ptr<Logic::Tile_Grid> &grid) const> functionMap;
        Entity_Register(functionMap);
        auto it = functionMap.find(entity_type);
        if (it == functionMap.end()) {
            throw std::runtime_error("Entity type " + entity_type + " not found");
        }
        auto memberFn = it->second;
        const std::shared_ptr<Logic::Model::Entity> model = (this->*memberFn)(conf, grid);

        if (data.contains("View")) {
            auto sfml_manager = conf.fr_->get_SFML_Manager();
            if (sfml_manager == nullptr) {
                throw std::runtime_error("Can't find sfml_manager");
            }

            nlohmann::json view = data["View"];
            Graphics::View::Actor_View_Info avi;
            if (view.contains("Sprite_Group")) {
                avi.sprite_group_name = view["Sprite_Group"].get<std::string>();
            }
            if (!view.contains("name")) {
                throw std::runtime_error("View dont have name");
            }
            avi.name = view["name"].get<std::string>();

            Graphics::Actor_Pair ap = Graphics::Graphics_Factory::make_Actor(sfml_manager, avi, model);
            conf.stage_->add_View(entity_type, ap.actor_view_);
        }
    }

    std::shared_ptr<Logic::Model::Entity> Reader_JSON::load_Actor(Stage_Info_JSON &conf) const {
        throw "Reader_JSON::load_Actor";
    }

    void Reader_JSON::Entity_Register(
        std::unordered_map<std::string, std::shared_ptr<Logic::Model::Entity>(Reader_JSON::*)(Stage_Info_JSON &conf)
        const> &outMap) const {
        throw std::runtime_error("Entity_Register: OLD");
    }

    void Reader_JSON::load_Entity(Stage_Info_JSON &conf) const {
        throw "load_Entity:: OLD";
    }

    std::shared_ptr<Stage> Reader_JSON::load_Game_Stage(const Reader_Base_Info_JSON &conf) const
    {
        nlohmann::json data = conf.data_;
        if (!data.contains("Type")) {
            throw std::runtime_error("Stage dont have Type");
        }
        const auto entity_type = data["Type"].get<std::string>();
        if (entity_type != "Game_Stage") {
            throw std::runtime_error("The load_Game_Stage method was called for a configuration other than Game_Stage.");
        }

        if (!data.contains("tile_grid")) {
            throw std::runtime_error("Stage dont have tile_grid");
        }
        if (!data.contains("camera_game")) {
            throw std::runtime_error("Stage dont have camera_game");
        }
        if (!data.contains("entities")) {
            throw std::runtime_error("Stage dont have entities");
        }

        const auto tile_grid = data["tile_grid"].get<std::string>();
        const auto camera_game = data["camera_game"].get<std::string>();
        const auto entities = data["entities"].get<std::string>();

        Graphics::Tile_Grid_Pair tgp = conf.fr_->load_Tile_Grid(tile_grid);
        std::shared_ptr<Graphics::Camera> game_camera = conf.fr_->load_Camera(camera_game);
        std::shared_ptr<Logic::Collision::World_Collision_Manager> wcm = std::make_shared<Logic::Collision::World_Collision_Manager>(
            std::make_shared<Logic::Collision::Separating_Axis_Theorem>(),
            tgp.tile_grid_model_
            );
        auto world = std::make_shared<Core::World>(tgp.tile_grid_model_, wcm, game_camera);
        for (const auto& view : tgp.terrain_views_) {
            world->add_View("Terrain", view);
        }

        conf.fr_->load_Entities(entities, world, tgp.tile_grid_model_);

        auto stage = std::make_shared<Core::Stage_Game>(world);

        return stage;
    }

    void Reader_JSON::Stage_Register(std::unordered_map<std::string, std::shared_ptr<Stage>(Reader_JSON::*)(const Reader_Base_Info_JSON &conf) const> &outMap) {
        outMap["Game_Stage"] = &Reader_JSON::load_Game_Stage;
    }

    std::shared_ptr<Logic::Collision::HitBoxe> Reader_JSON::load_HitBox_Rectangle(const nlohmann::json &info) const {

        if (!info.contains("Type")) {
            throw std::runtime_error("HitBox_Rectangle dont have Type");
        }
        auto type = info["Type"].get<std::string>();
        if (type != "HitBox_Rectangle") {
            throw std::runtime_error("The load_HitBox_Rectangle method was called for a configuration other than HitBox_Rectangle.");
        }

        int layer = 0;
        int strength = 0;
        if (!info.contains("position")) {
            throw std::runtime_error("HitBox_Rectangle dont have position");
        }
        if (!info.contains("width")) {
            throw std::runtime_error("HitBox_Rectangle dont have width");
        }
        if (!info.contains("height")) {
            throw std::runtime_error("HitBox_Rectangle dont have height");
        }
        if (info.contains("layer")) {
            layer= info["layer"].get<int>();
        }
        if (info.contains("strength")) {
            strength = info["strength"].get<int>();
        }
        Math::Vector2 position = from_json(info["position"]);
        auto width = info["width"].get<float>();
        auto height = info["height"].get<float>();

        return std::make_shared<Logic::Collision::HitBox_Rectangle>(position, width, height, layer, strength);
    }

    void Reader_JSON::HitBoxe_Register(
        std::unordered_map<std::string, std::shared_ptr<Logic::Collision::HitBoxe>(Reader_JSON::*)(const nlohmann::json& info) const> &outMap) const {
        outMap["HitBox_Rectangle"] = &Reader_JSON::load_HitBox_Rectangle;
    }


    nlohmann::json Reader_JSON::get_json_data(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file " + filename + "!\n";
            throw std::runtime_error("File not opened");
        }
        nlohmann::json data;
        file >> data;
        file.close();
        return data;
    }
}