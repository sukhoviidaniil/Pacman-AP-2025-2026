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

#include "core/stages/World.h"

namespace Core {
    World::World(
        const std::shared_ptr<Logic::Tile_Grid> &grid,
        const std::shared_ptr<Logic::Collision::World_Collision_Manager> &WCM,
        const std::shared_ptr<Graphics::Camera> &game_camera):
        grid_(grid), WCM_(WCM), game_camera_(game_camera){
    }

    World::~World() = default;

    void World::add_Model(const std::string &type, const std::shared_ptr<Model> &model) {
        const std::string& name = model->get_name();

        // Uniqueness check
        if (models_by_name.contains(name)) {
            throw std::runtime_error("Model with name '" + name + "' already exists");
        }

        // Add to list by type
        auto& vec = models_by_type[type];
        size_t index = vec.size();
        vec.push_back(model);

        // Create a record
        Model_Entry entry;
        entry.name = name;
        entry.type = type;
        entry.index_in_type_vector = index;
        entry.model = model;

        models_by_name.emplace(name, std::move(entry));
    }

    std::vector<std::shared_ptr<Model>> World::get_Models(const std::string &type) const {
        auto it = models_by_type.find(type);
        if (it == models_by_type.end()) {
            return {}; // empty list
        }
        return it->second; // copy
    }

    std::shared_ptr<Model> World::get_Model(const std::string &type, const std::string &name) const {
        auto it = models_by_name.find(name);
        if (it == models_by_name.end()) {
            return nullptr;
        }

        // Check that the type is correct
        if (it->second.type != type) {
            return nullptr; // or throw an exception
        }

        return it->second.model;
    }

    void World::add_View(const std::string &type, const std::shared_ptr<View> &view) {
        const std::string& name = view->get_name();

        // Uniqueness check
        if (view_by_name.contains(name)) {
            throw std::runtime_error("View with name '" + name + "' already exists");
        }

        // Add to list by type
        auto& vec = view_by_type[type];
        size_t index = vec.size();
        vec.push_back(view);

        // Creating a record
        View_Entry entry;
        entry.name = name;
        entry.type = type;
        entry.index_in_type_vector = index;
        entry.view = view;

        view_by_name.emplace(name, std::move(entry));
    }

    std::vector<std::shared_ptr<View>> World::get_Views(const std::string &type) const {
        auto it = view_by_type.find(type);
        if (it == view_by_type.end()) {
            return {};
        }
        return it->second; // copy
    }

    std::shared_ptr<View> World::get_View(const std::string &type, const std::string &name) const {
        auto it = view_by_name.find(name);
        if (it == view_by_name.end()) {
            return nullptr;
        }

        // Проверка совпадения типа
        if (it->second.type != type) {
            return nullptr;
        }

        return it->second.view;
    }

    std::shared_ptr<Logic::Tile_Grid> World::get_grid() {
        return grid_;
    }

    void World::simulate(float delta) {
        // Iteration through all types
        for (auto& [type, vec] : view_by_type){
            // Go through each View in the type
            for (auto& view_ptr : vec){
                if (!view_ptr) continue; // nullptr protection
                // TODO
            }
        }
    }

    void World::render(sf::RenderWindow &window) {
        // Iteration through all types
        for (auto& [type, vec] : view_by_type){
            // Go through each View in the type
            for (auto& view_ptr : vec){
                if (!view_ptr) continue; // nullptr protection
                game_camera_->render(window, view_ptr);
            }
        }
    }

}
