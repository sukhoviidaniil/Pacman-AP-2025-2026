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

namespace Graphics {
    Actor_Pair Graphics_Factory::make_Actor(
        const SFML_Manager &manager, const View::Actor_View_Info &view_info,
        const Logic::Model::Actor_Info &model_info) {
        std::shared_ptr<Logic::Model::Actor> actor_model = Logic::Logic_Factory::make_Actor(model_info);
        if (actor_model == nullptr) {
            throw std::runtime_error("Failed to create actor!");
        }
        return make_Actor(manager, view_info, actor_model);
    }

    Actor_Pair Graphics_Factory::make_Actor(const SFML_Manager &manager, const View::Actor_View_Info &view_info,
        const std::shared_ptr<Logic::Model::Actor> &actor_model) {

        std::shared_ptr<Sprite_Group> sprite_group = manager.get_Sprite_Group(view_info.sprite_group_name);
        if (sprite_group == nullptr) {
            throw std::runtime_error("Failed to create sprite group!");
        }
        auto actor_view = std::make_shared<View::Actor_View>(sprite_group);
        actor_view->set_actor_model(actor_model);
        return Actor_Pair(actor_model, actor_view);
    }

    Tile_Grid_Pair Graphics_Factory::make_Tile_Grid(
        const SFML_Manager &manager,
        const Logic::Tile_Grid_Info &tile_grid_info) {
        std::shared_ptr<Logic::Tile_Grid> tile_grid_model = Logic::Logic_Factory::make_grid(tile_grid_info);
        if (tile_grid_model == nullptr) {
            throw std::runtime_error("Failed to create tile grid!");
        }
        // TODO ADD GRID VIEW
        throw;
    }

}
