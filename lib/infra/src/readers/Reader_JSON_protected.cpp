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


namespace infra {

    /*

    std::shared_ptr<logic::model::Entity> Reader_JSON::load_Actor(Stage_Info_JSON& conf, const std::shared_ptr<logic::Tile_Grid> &grid) const{
        const nlohmann::json &data = conf.data_;

        if (!data.contains("Type")) {
            throw std::runtime_error("Entity.Type missing or invalid");
        }
        if (!data.contains("Model")) {
            throw std::runtime_error("Entity.Model missing or invalid");
        }

        const auto type = data["Type"].get<std::string>();
        std::shared_ptr<logic::model::Entity> model;

        if (data["Model"].is_object()) {
            nlohmann::json model_data = data["Model"];
            logic::model::Actor_Info actor_info;

            actor_info.name = model_data.value("name", actor_info.name);

            if (model_data.contains("speed") && model_data["speed"].is_number()) {
                actor_info.speed = model_data["speed"].get<float>();
            }else {
                throw std::runtime_error("Entity.Model.speed missing or invalid");
            }

            if (model_data.contains("position") && model_data["position"].is_object()) {
                actor_info.position = grid->get_nearest_tile_center(from_json(model_data["position"]));
            }else {
                throw std::runtime_error("Entity.Model.position missing or invalid");
            }

            if (model_data.contains("max_status") && model_data["max_status"].is_number()) {
                actor_info.max_status = model_data["max_status"].get<int>();
            }else {
                throw std::runtime_error("Entity.Model.max_status missing or invalid");
            }

            if (model_data.contains("hitbox") && model_data["hitbox"].is_string()) {
                const auto hitbox = model_data["hitbox"].get<std::string>();
                actor_info.hitbox = conf.fr_->make_HitBoxe(hitbox);
            }else {
                throw std::runtime_error("Entity.Model.hitbox missing or invalid");
            }

            model = logic::Logic_Factory::make_Actor(actor_info);
            conf.stage_->add_model(type, model);
        }

        if (data["Model"].is_string()){
            const auto actor_name = data["Model"].get<std::string>();
            model = conf.stage_->get_model(type, actor_name);
        }else {
            throw std::runtime_error("Entity.Model missing or invalid");
        }

        if (model == nullptr) throw std::runtime_error("Actor model not added");
        return model;
    }

    void Reader_JSON::Entity_Register(std::unordered_map<std::string, std::shared_ptr<logic::model::Entity>(Reader_JSON::*)(Stage_Info_JSON &conf, const std::shared_ptr<logic::Tile_Grid> &grid) const> &outMap) const {
        outMap["Actor"] = &Reader_JSON::load_Actor;
    }

    void Reader_JSON::load_Entity(Stage_Info_JSON &conf, const std::shared_ptr<logic::Tile_Grid> &grid) const {
        const nlohmann::json &data = conf.data_;
        if (!data.contains("Type")) {
            throw std::runtime_error("Entity dont have Type");
        }
        const std::string entity_type = data["Type"].get<std::string>();

        std::unordered_map<
            std::string,
            std::shared_ptr<logic::model::Entity>(Reader_JSON::*)(Stage_Info_JSON &conf, const std::shared_ptr<logic::Tile_Grid> &grid) const> functionMap;
        Entity_Register(functionMap);
        auto it = functionMap.find(entity_type);
        if (it == functionMap.end()) {
            throw std::runtime_error("Entity type " + entity_type + " not found");
        }

        auto memberFn = it->second;
        const std::shared_ptr<logic::model::Entity> model = (this->*memberFn)(conf, grid);

        if (data.contains("View")) {
            auto sfml_manager = conf.fr_->get_SFML_Manager();
            if (sfml_manager == nullptr) {
                throw std::runtime_error("Can't find sfml_manager");
            }

            nlohmann::json view = data["View"];
            graphics::view::Actor_View_Info avi;
            if (view.contains("Sprite_Group")) {
                avi.sprite_group_name = view["Sprite_Group"].get<std::string>();
            }
            if (!view.contains("name")) {
                throw std::runtime_error("View dont have name");
            }
            avi.name = view["name"].get<std::string>();

            graphics::Actor_Pair ap = graphics::Graphics_Factory::make_Actor(sfml_manager, avi, model);
            conf.stage_->add_View(entity_type, ap.actor_view_);
        }
    }

    void Reader_JSON::Entity_Register(
        std::unordered_map<std::string, std::shared_ptr<logic::model::Entity>(Reader_JSON::*)(Stage_Info_JSON &conf)
        const> &outMap) const {
        throw std::runtime_error("Entity_Register: OLD");
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

        graphics::Tile_Grid_Pair tgp = conf.fr_->load_Tile_Grid(tile_grid);
        std::shared_ptr<graphics::Camera> game_camera = conf.fr_->load_Camera(camera_game);
        std::shared_ptr<logic::collision::World_Collision_Manager> wcm = std::make_shared<logic::collision::World_Collision_Manager>(
            std::make_shared<logic::collision::Separating_Axis_Theorem>(),
            tgp.tile_grid_model_
            );
        auto world = std::make_shared<core::World>(tgp.tile_grid_model_, wcm, game_camera);
        for (const auto& view : tgp.terrain_views_) {
            world->add_View("Terrain", view);
        }

        conf.fr_->load_Entities(entities, world, tgp.tile_grid_model_);

        auto stage = std::make_shared<core::Stage_Game>(world);

        return stage;
    }

    void Reader_JSON::Stage_Register(std::unordered_map<std::string, std::shared_ptr<Stage>(Reader_JSON::*)(const Reader_Base_Info_JSON &conf) const> &outMap) {
        outMap["Game_Stage"] = &Reader_JSON::load_Game_Stage;
    }

    std::shared_ptr<logic::collision::HitBoxe> Reader_JSON::load_HitBox_Rectangle(const nlohmann::json &data) const {

        auto type = get_checked<std::string>(data, TODO, "Type", "Root");
        if (type != "HitBox_Rectangle") {
            throw std::runtime_error("The load_HitBox_Rectangle method was called for a configuration other than HitBox_Rectangle.");
        }

        int layer = get_checked<std::string>(data, TODO, "Type", "Root");;
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
        math::Vector2 position = get_checked<std::string>(data, TODO, "Type", "Root");

        math::Vector2 position = from_json(info["position"]);
        auto width = info["width"].get<float>();
        auto height = info["height"].get<float>();

        return std::make_shared<logic::collision::HitBox_Rectangle>(position, width, height, layer, strength);
    }

    void Reader_JSON::HitBoxe_Register(
        std::unordered_map<
            std::string,
            std::shared_ptr<logic::collision::HitBoxe>(Reader_JSON::*)(const nlohmann::json& info) const
            > &outMap) const {
        outMap["HitBox_Rectangle"] = &Reader_JSON::load_HitBox_Rectangle;
    }
    */
}
