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

    void World::add_Actor_Model(const std::shared_ptr<Logic::Model::Actor> &actor) {
        std::string actor_name = actor->get_name();
        auto it = actors_.find(actor_name);
        if (it == actors_.end()) {
            it->second = actor;
            return;
        }
        throw std::runtime_error("Actor_Model already exists!");
    }

    std::shared_ptr<Logic::Model::Actor> World::get_Actor_Model(const std::string &name) {
        auto it = actors_.find(name);
        if (it != actors_.end()) {
            return it->second;
        }
        return nullptr;
    }

    void World::get_Actor_View(const std::string &name) {

    }

    void World::get_Entity_View(const std::string &name) {
    }

    void World::set_entity_model(const std::unordered_map<std::string, std::vector<std::shared_ptr<Logic::Model::Entity>>> &entity_model) {
        entity_model_ = entity_model;
    }

    void World::set_entity_view(const std::vector<std::shared_ptr<Graphics::View::Entity_View>>& entity_view) {
        entity_view_ = entity_view;
    }

    void World::add_entity(const std::string &type, std::shared_ptr<Logic::Model::Entity> entity) {
        auto it = entity_model_.find(type);
        if (it != entity_model_.end()) {
            it->second.push_back(entity);
        }else {
            it->second = {entity};
        }
    }

    void World::add_entity_view(const std::shared_ptr<Graphics::View::Entity_View> &entity_view) {
        entity_view_.push_back(entity_view);
    }

    std::vector<std::shared_ptr<Logic::Model::Entity>> World::get_entities(const std::string &type) {
        auto it = entity_model_.find(type);
        if (it != entity_model_.end()) {
            return it->second;
        }
        return std::vector<std::shared_ptr<Logic::Model::Entity>>();
    }

    std::shared_ptr<Logic::Tile_Grid> World::get_grid() {
        return grid_;
    }

    void World::simulate(float delta) {

    }

    void World::render(sf::RenderWindow &window) {

    }
}
