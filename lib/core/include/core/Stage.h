/***************************************************************
 * Project:       Pacman
 * File:          Stage.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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
#ifndef PACMAN_STAGE_H
#define PACMAN_STAGE_H

#include "Stage_Manager.h"
#include "graphics/View.h"
#include "logic/model/Entity.h"
#include "SFML/graphics/RenderWindow.hpp"

namespace core {

    struct model_Entry {
        std::string name;
        std::string type;
        size_t index_in_type_vector; // position in vector
        std::shared_ptr<logic::model::Entity> model;
    };

    struct View_Entry {
        std::string name;
        std::string type;
        size_t index_in_type_vector; // position in vector
        std::shared_ptr<graphics::View> view;
    };

    struct Stage_Info {
        std::string name = "default";
        std::string configuration = "default";
    };

    class Stage {

        std::shared_ptr<Stage_Manager> manager;

        public:
        Stage();
        virtual ~Stage();

        /**
         * Adds a model to the world's model container.
         * Name of the model must be unique across the world.
         *
         * @param type Type/category of the model
         * @param model Shared pointer to the model
         * @throw std::runtime_error if a model with the same name already exists
         */
        virtual void add_model(const std::string& type, const std::shared_ptr<logic::model::Entity>& model) = 0;

        /**
         * Returns all models of a given type.
         *
         * @param type Type/category of models
         * @return Vector of shared pointers to models of the specified type;
         *         empty vector if type does not exist
         */
        [[nodiscard]] virtual std::vector<std::shared_ptr<logic::model::Entity>> get_models(const std::string& type) const = 0;

        /**
         * Returns a model by its type and name.
         *
         * @param type Type/category of the model
         * @param name Name of the model
         * @return Shared pointer to the model, or nullptr if not found or type mismatch
         */
        [[nodiscard]] virtual std::shared_ptr<logic::model::Entity> get_model(const std::string& type, const std::string& name) const = 0;

        /**
         * Adds a view to the world's view container.
         * Name of the view must be unique across the world.
         *
         * @param type Type/category of the view
         * @param view Shared pointer to the view
         * @throw std::runtime_error if a view with the same name already exists
         */
        virtual void add_View(const std::string& type, const std::shared_ptr<graphics::View>& view) = 0;

        /**
         * Returns all views of a given type.
         *
         * @param type Type/category of views
         * @return Vector of shared pointers to views of the specified type;
         *         empty vector if type does not exist
         */
        [[nodiscard]] virtual std::vector<std::shared_ptr<graphics::View>> get_Views(const std::string& type) const = 0;

        /**
         * Returns a view by its type and name.
         *
         * @param type Type/category of the view
         * @param name Name of the view
         * @return Shared pointer to the view, or nullptr if not found or type mismatch
         */
        [[nodiscard]] virtual std::shared_ptr<graphics::View> get_View(const std::string& type, const std::string& name) const = 0;

        virtual void simulate(float delta) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

        virtual void pause() = 0;
    };
}

#endif //PACMAN_STAGE_H