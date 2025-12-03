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

#include "SFML_Manager.h"
#include "logic/model/Actor.h"
#include "graphics/view/Actor_View.h"
#include "view/Tile_Grid_View.h"

namespace Graphics {

    struct Actor_Pair {
        std::shared_ptr<Logic::Model::Actor> actor_model_;
        std::shared_ptr<View::Actor_View> actor_view_;
    };

    struct Tile_Grid_Pair {
        std::shared_ptr<Logic::Tile_Grid> tile_grid_model_;
        std::shared_ptr<View::Tile_Grid_View> tile_grid_view_;
        std::vector<std::shared_ptr<View::Terrain_View>> terrain_views_;
    };

    class Graphics_Factory{
        public:
        static Actor_Pair make_Actor(
            const std::shared_ptr<SFML_Manager>& manager,
            const View::Actor_View_Info &view_info,
            const Logic::Model::Actor_Info &model_info
            );
        static Actor_Pair make_Actor(
            const std::shared_ptr<SFML_Manager>& manager,
            const View::Actor_View_Info &view_info,
            const std::shared_ptr<Logic::Model::Actor>& actor_model);

        static Tile_Grid_Pair make_Tile_Grid(const std::shared_ptr<SFML_Manager>& manager, const Logic::Tile_Grid_Info &tile_grid_info);
    };

}

#endif //PACMAN_GRAPHICS_FACTORY_H