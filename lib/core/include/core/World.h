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
        std::shared_ptr<Logic::Tile_Grid> grid_;
        std::shared_ptr<Logic::Collision::World_Collision_Manager> WCM_;
        std::shared_ptr<Graphics::Camera> game_camera_;

        std::unordered_map<
            std::string,
            std::shared_ptr<Logic::Model::Actor>
        >actors_;

        std::vector<std::shared_ptr<Logic::Model::Entity>> collectable_; // TODO ADD TYPE

        std::unordered_map<
            std::string,
            std::vector<
                std::shared_ptr<Logic::Model::Entity>
            >
        > entity_model_;

        std::vector<
            std::shared_ptr<Graphics::View::Entity_View>
        > entity_view_;

        public:
        World(
            const std::shared_ptr<Logic::Tile_Grid> &grid,
            const std::shared_ptr<Logic::Collision::World_Collision_Manager> &WCM,
            const std::shared_ptr<Graphics::Camera> &game_camera
            );
        ~World();



        void add_Actor_Model(const std::shared_ptr<Logic::Model::Actor>& actor);
        std::shared_ptr<Logic::Model::Actor> get_Actor_Model(const std::string& name);

        void get_Actor_View(const std::string& name);
        void get_Entity_View(const std::string& name);

        void set_entity_model(const std::unordered_map<std::string,std::vector<std::shared_ptr<Logic::Model::Entity>>> &entity_model);
        void set_entity_view(const std::vector<std::shared_ptr<Graphics::View::Entity_View>>& entity_view);

        void add_entity(const std::string& type, std::shared_ptr<Logic::Model::Entity> entity);
        void add_entity_view(const std::shared_ptr<Graphics::View::Entity_View> &entity_view);

        std::vector<std::shared_ptr<Logic::Model::Entity>> get_entities(const std::string& type);
        std::shared_ptr<Logic::Tile_Grid> get_grid();

        void simulate(float delta);
        void render(sf::RenderWindow& window);
    };
}

#endif //PACMAN_WORLD_H