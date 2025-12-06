/***************************************************************
 * Project:       Pacman
 * File:          World.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-30
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

#include "core/World.h"

namespace Core {
    World::World(
        const std::shared_ptr<Logic::Tile_Grid> &grid,
        const std::shared_ptr<Logic::Collision::World_Collision_Manager> &WCM,
        const std::shared_ptr<Graphics::Camera> &game_camera):
        grid_(grid), WCM_(WCM), game_camera_(game_camera){
    }

    World::~World() = default;

    void World::add_Actor_Model(const std::shared_ptr<Logic::Model::Entity> &actor) {
        std::string actor_name = actor->get_name();
        auto it = actors_models_.find(actor_name);
        if (it == actors_models_.end()) {
            it->second = actor;
            return;
        }
        throw std::runtime_error("Actor_Model already exists!");
    }

    std::shared_ptr<Logic::Model::Entity> World::get_Actor_Model(const std::string &name) {
        auto it = actors_models_.find(name);
        if (it != actors_models_.end()) {
            return it->second;
        }
        return nullptr;
    }

    void World::add_Actor_View(const std::shared_ptr<Graphics::View::View> &actor_view) {
        std::string name = actor_view->get_name();
        auto it = actors_views_.find(name);
        if (it == actors_views_.end()) {
            actors_views_[name] = {actor_view};
        }else {
            it->second.emplace_back(actor_view);
        }
    }

    void World::add_entity_view(const std::shared_ptr<Graphics::View::View> &entity_view) {
        gen_view_.push_back(entity_view);
    }

    std::shared_ptr<Logic::Tile_Grid> World::get_grid() {
        return grid_;
    }

    void World::simulate(float delta) {

    }

    void World::render(sf::RenderWindow &window) {

    }
}
