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


#include "core/Stage.h"
#include "graphics/Camera.h"
#include "logic/Tile_Grid.h"
#include "logic/collision/World_Collision_Manager.h"

namespace core {
    class World : public Stage{
        std::shared_ptr<logic::Tile_Grid> grid_;
        std::shared_ptr<logic::collision::World_Collision_Manager> WCM_;
        std::shared_ptr<graphics::Camera> game_camera_;

        std::unordered_map<
            std::string,
            model_Entry
        > models_by_name;

        std::unordered_map<
            std::string,
            std::vector<std::shared_ptr<logic::model::Entity>>
        > models_by_type;

        std::unordered_map<
            std::string,
            std::vector<std::shared_ptr<graphics::View>>
        > view_by_type;

        public:
        World(
            const std::shared_ptr<logic::Tile_Grid> &grid,
            const std::shared_ptr<logic::collision::World_Collision_Manager> &WCM,
            const std::shared_ptr<graphics::Camera> &game_camera
            );

        ~World() override;

        /**
         * Adds a model to the world's model container.
         * Name of the model must be unique across the world.
         *
         * @param type Type/category of the model
         * @param model Shared pointer to the model
         * @throw std::runtime_error if a model with the same name already exists
         */
        void add_model(const std::string& type, const std::shared_ptr<logic::model::Entity>& model) override;

        /**
         * Returns all models of a given type.
         *
         * @param type Type/category of models
         * @return Vector of shared pointers to models of the specified type;
         *         empty vector if type does not exist
         */
        std::vector<std::shared_ptr<logic::model::Entity>> get_models(const std::string& type) const override;

        /**
         * Returns a model by its type and name.
         *
         * @param type Type/category of the model
         * @param name Name of the model
         * @return Shared pointer to the model, or nullptr if not found or type mismatch
         */
        std::shared_ptr<logic::model::Entity> get_model(const std::string& type, const std::string& name) const override;

        /**
         * Adds a view to the world's view container.
         * Name of the view must be unique across the world.
         *
         * @param type Type/category of the view
         * @param view Shared pointer to the view
         * @throw std::runtime_error if a view with the same name already exists
         */
        void add_View(const std::string& type, const std::shared_ptr<graphics::View>& view) override;

        /**
         * Returns all views of a given type.
         *
         * @param type Type/category of views
         * @return Vector of shared pointers to views of the specified type;
         *         empty vector if type does not exist
         */
        std::vector<std::shared_ptr<graphics::View>> get_Views(const std::string& type) const  override;

        /**
         * Returns a view by its type and name.
         *
         * @param type Type/category of the view
         * @param name Name of the view
         * @return Shared pointer to the view, or nullptr if not found or type mismatch
         */
        std::shared_ptr<graphics::View> get_View(const std::string& type, const std::string& name) const override;

        std::shared_ptr<logic::Tile_Grid> get_grid();

        void simulate(float delta) override;
        void render(sf::RenderWindow& window) override;
    };
}

#endif //PACMAN_WORLD_H