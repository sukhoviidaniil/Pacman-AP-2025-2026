/***************************************************************
 * Project:       Pacman
 * File:          Graphics_Factory.cpp
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

#include "view/Graphics_Factory.h"

namespace view {
    std::shared_ptr<View> Graphics_Factory::make_View(const infra::ast::View &info, const std::string &path) {
        std::unordered_map<std::string, std::shared_ptr<View>(*)(const infra::ast::View&, const std::string&)> map;
        Register(map);
        std::string type = info.type;
        auto it = map.find(type);
        if (it != map.end()) {
            return it->second(info, path);
        }
        throw std::runtime_error("Unknown view type: " + type);
    }

    void Graphics_Factory::Register(
        std::unordered_map<std::string, std::shared_ptr<View>(*)(const infra::ast::View&, const std::string&)> &outMap
        ) {
        outMap["SFML"] = &Graphics_Factory::SFML_View;

    }

    std::shared_ptr<View> Graphics_Factory::SFML_View(const infra::ast::View& info, const std::string& path) {

    }
}

/*

#include "logic/Logic_Factory.h"

namespace graphics {
    std::shared_ptr<Camera> Graphics_Factory::make_Camera(const Camera_Info &info) {
        return std::make_shared<Camera>(info);
    }

    Actor_Pair Graphics_Factory::make_Actor(
        const std::shared_ptr<SFML_Manager> &manager,
        const view::Actor_View_Info &view_info,
        const logic::model::Actor_Info &model_info
        ) {
        std::shared_ptr<logic::model::Entity> actor_model = logic::Logic_Factory::make_Actor(model_info);
        if (actor_model == nullptr) {
            throw std::runtime_error("Failed to create actor!");
        }
        return make_Actor(manager, view_info, actor_model);
    }

    Actor_Pair Graphics_Factory::make_Actor(
        const std::shared_ptr<SFML_Manager> &manager,
        const view::Actor_View_Info &view_info,
        const std::shared_ptr<logic::model::Entity> &actor_model
        ) {

        std::shared_ptr<Sprite_Group> sprite_group = manager->get_Sprite_Group(view_info.sprite_group_name);
        if (sprite_group == nullptr) {
            throw std::runtime_error("Failed to get sprite group!");
        }
        auto actor_view = std::make_shared<view::Actor_View>(sprite_group, view_info.name);
        actor_view->set_Entity(actor_model);
        return Actor_Pair(actor_model, actor_view);
    }

    TileGrid_Pair Graphics_Factory::make_TileGrid(
        const std::shared_ptr<SFML_Manager> &manager,
        const logic::TileGrid_Info &tile_grid_info
        ) {
        TileGrid_Pair p;
        p.tile_grid_model_ = logic::Logic_Factory::make_grid(tile_grid_info);
        if (p.tile_grid_model_ == nullptr) {
            throw std::runtime_error("Failed to create tile grid!");
        }
        std::vector<std::vector<std::shared_ptr<logic::Tile>>> all_tiles = p.tile_grid_model_->get_tiles();

        for (const auto &tile_line : all_tiles) {
            for (const auto &tile : tile_line) {
                std::shared_ptr<logic::model::Entity> terrain = tile->get_terrain();
                std::string name = terrain->get_name();
                std::shared_ptr<sf::Sprite> tile_sprite = manager->get_Sprite(name);
                auto terrain_view = std::make_shared<view::Terrain_View>(terrain, tile_sprite);
                p.terrain_views_.push_back(terrain_view);
            }
        }
        return p;
    }
}
*/
