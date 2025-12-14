/***************************************************************
 * Project:       Pacman
 * File:          Graphics_Factory.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-28
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
#ifndef PACMAN_GRAPHICS_FACTORY_H
#define PACMAN_GRAPHICS_FACTORY_H

#include "sfml/SFML_Manager.h"
#include "logic/model/Actor.h"
#include "view/entity/Actor_View.h"
#include "view/entity/Terrain_View.h"
#include "graphics/Camera.h"

namespace graphics {

    struct Actor_Pair {
        std::shared_ptr<logic::model::Entity> actor_model_;
        std::shared_ptr<View> actor_view_;
    };

    struct Tile_Grid_Pair {
        std::shared_ptr<logic::Tile_Grid> tile_grid_model_;
        std::vector<std::shared_ptr<View>> terrain_views_; // TODO view::Terrain_View -> View
    };

    class Graphics_Factory{
        public:

        static std::shared_ptr<Camera> make_Camera(const Camera_Info& info);
        static Actor_Pair make_Actor(
            const std::shared_ptr<SFML_Manager>& manager,
            const view::Actor_View_Info &view_info,
            const logic::model::Actor_Info &model_info
            );
        static Actor_Pair make_Actor(
            const std::shared_ptr<SFML_Manager>& manager,
            const view::Actor_View_Info &view_info,
            const std::shared_ptr<logic::model::Entity>& model);

        static Tile_Grid_Pair make_Tile_Grid(const std::shared_ptr<SFML_Manager>& manager, const logic::Tile_Grid_Info &tile_grid_info);
    };

}

#endif //PACMAN_GRAPHICS_FACTORY_H