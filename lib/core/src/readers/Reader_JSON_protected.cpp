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

#include "core/File_Reader.h"
#include "core/readers/Reader_JSON.h"
#include "graphics/Graphics_Factory.h"
#include "logic/Logic_Factory.h"

namespace Core {
        void Reader_JSON::add_Actor(
        const std::shared_ptr<const File_Reader> &fr,
        std::shared_ptr<World> &world,
        const nlohmann::json &model) {
        Logic::Model::Actor_Info actor_info;
        actor_info.name = model["name"].get<std::string>();
        actor_info.position = from_json(model["position"]);
        actor_info.speed = model["speed"].get<float>();
        actor_info.max_status = model["max_status"].get<unsigned int>();
        const std::string hitbox = model["hitbox"].get<std::string>();
        actor_info.hitbox = fr->make_HitBoxe(hitbox);
        std::shared_ptr<Logic::Model::Entity> actor = Logic::Logic_Factory::make_Actor(actor_info);
        world->add_Actor_Model(actor);
    }

    void Reader_JSON::add_Actor(Entity_JSON_Info& conf) const{
        const nlohmann::json &info = conf.info;
        std::string actor_name;
        if (info["Model"].is_object()) {
            nlohmann::json model = info["Model"];
            actor_name = model["name"].get<std::string>();
            add_Actor(conf.fr, conf.world, model);
        }else {
            actor_name = info["Model"].get<std::string>();
        }
        std::shared_ptr<Logic::Model::Entity> actor_model = conf.world->get_Actor_Model(actor_name);
        if (actor_model == nullptr) throw std::runtime_error("Actor model not added");

        if (info.contains("View")) {
            nlohmann::json view = info["View"];
            if (view.contains("Sprite_Group")) {
                Graphics::View::Actor_View_Info avi;
                avi.sprite_group_name = actor_name;
                auto sfml_manager = conf.fr->get_SFML_Manager();
                if (sfml_manager == nullptr) {
                    throw std::runtime_error("Can't find sfml_manager");
                }
                Graphics::Actor_Pair ap = Graphics::Graphics_Factory::make_Actor(sfml_manager, avi, actor_model);
                conf.world->add_entity_view(ap.actor_view_);
            }
        }

    }

    void Reader_JSON::Entity_Register(std::unordered_map<std::string, void(Reader_JSON::*)(Entity_JSON_Info &conf) const> &outMap) const {
        outMap["Actor"] = &Reader_JSON::add_Actor;
    }

    void Reader_JSON::add_Entity(Entity_JSON_Info &conf) const {
        std::unordered_map<std::string, void(Reader_JSON::*)(Entity_JSON_Info &conf) const> functionMap;
        Entity_Register(functionMap);
        const nlohmann::json &info = conf.info;
        if (!info.contains("Type")) {
            throw std::runtime_error("Entity dont have Type");
        }
        const std::string entity_type = info["Type"].get<std::string>();
        if (!info.contains("Model")) {
            throw std::runtime_error("Entity dont have Model");
        }
        auto it = functionMap.find(entity_type);
        if (it != functionMap.end()) {
            auto memberFn = it->second;
            (this->*memberFn)(conf);
        }else {
            throw std::runtime_error("Entity type " + entity_type + " not found");
        }
    }

    std::shared_ptr<Stage> Reader_JSON::load_Game_Stage(const Reader_JSON_Base_Info &conf) const {

    }

    void Reader_JSON::Stage_Register(std::unordered_map<std::string, std::shared_ptr<Stage>(Reader_JSON::*)(const Reader_JSON_Base_Info &conf) const> &outMap) {
        outMap["Game_Stage"] = &Reader_JSON::load_Game_Stage;
    }

    void Reader_JSON::HitBoxe_Register(
        std::unordered_map<std::string, void(Reader_JSON::*)(const Reader_JSON_Base_Info &conf) const> &outMap) const {
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
