/***************************************************************
 * Project:       Pacman
 * File:          World.h
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
#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H


#include "graphics/Camera.h"
#include "graphics/view/Actor_View.h"
#include "logic/Tile_Grid.h"
#include "logic/collision/World_Collision_Manager.h"

namespace Core {
    class World {

        std::vector<
            std::shared_ptr<Logic::Model::Entity>
        > entity_model_;
        std::shared_ptr<Logic::Tile_Grid> grid_;
        std::shared_ptr<Logic::Collision::World_Collision_Manager> WCM_;


        std::vector<
            std::shared_ptr<Graphics::View::Entity_View>
        > entity_view_;

        std::shared_ptr<Graphics::Camera> game_camera_;


    };
}

#endif //PACMAN_WORLD_H