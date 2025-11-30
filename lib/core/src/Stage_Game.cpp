/***************************************************************
 * Project:       Pacman
 * File:          Stage_Game.cpp
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

#include "core/Stage_Game.h"

namespace Core {
    Stage_Game::Stage_Game(
        const std::vector<std::shared_ptr<Logic::Model::Entity>> &entity_model,
        const std::shared_ptr<Logic::Tile_Grid> &grid,
        const std::shared_ptr<Logic::Collision::World_Collision_Manager> &WCM,
        const std::vector<std::shared_ptr<Graphics::View::Entity_View>> &entity_view,
        const std::shared_ptr<Graphics::Camera> &game_camera):
        entity_model_(entity_model),
        grid_(grid),
        WCM_(WCM),
        entity_view_(entity_view),
        game_camera_(game_camera){

    }

    Stage_Game::~Stage_Game() = default;

    void Stage_Game::simulate() {

    }

    void Stage_Game::render(sf::RenderWindow& window) {
        game_camera_->render(window, entity_view_);
    }
}
