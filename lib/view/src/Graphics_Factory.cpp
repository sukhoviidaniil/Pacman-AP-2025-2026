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

#include "graphics/Graphics_Factory.h"

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

    Tile_Grid_Pair Graphics_Factory::make_Tile_Grid(
        const std::shared_ptr<SFML_Manager> &manager,
        const logic::Tile_Grid_Info &tile_grid_info
        ) {
        Tile_Grid_Pair p;
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
