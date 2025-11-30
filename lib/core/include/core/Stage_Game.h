/***************************************************************
 * Project:       Pacman
 * File:          Stage_Game.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-24
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
#ifndef PACMAN_STAGE_GAME_H
#define PACMAN_STAGE_GAME_H


#include "Stage.h"
#include "graphics/Camera.h"
#include "graphics/view/Actor_View.h"
#include "logic/Tile_Grid.h"
#include "logic/collision/World_Collision_Manager.h"

#include <memory>

namespace Core {
    class Stage_Game : Stage {

        std::vector<
            std::shared_ptr<Logic::Model::Entity>
        > entity_model_;
        std::shared_ptr<Logic::Tile_Grid> grid_;
        std::shared_ptr<Logic::Collision::World_Collision_Manager> WCM_;


        std::vector<
            std::shared_ptr<Graphics::View::Entity_View>
        > entity_view_;

        std::shared_ptr<Graphics::Camera> game_camera_;

        public:

        Stage_Game(
            const std::vector<std::shared_ptr<Logic::Model::Entity>> &entity_model,
            const std::shared_ptr<Logic::Tile_Grid> &grid,
            const std::shared_ptr<Logic::Collision::World_Collision_Manager> &WCM,
            const std::vector<std::shared_ptr<Graphics::View::Entity_View>> &entity_view,
            const std::shared_ptr<Graphics::Camera> &game_camera
            );
        ~Stage_Game() override;

        void simulate() override;
        void render(sf::RenderWindow& window) override;
    };
}

#endif //PACMAN_STAGE_GAME_H