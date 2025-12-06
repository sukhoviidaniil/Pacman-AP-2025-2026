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


#include "Stage.h"
#include "graphics/Camera.h"
#include "graphics/view/entity/Actor_View.h"
#include "logic/Tile_Grid.h"
#include "logic/collision/World_Collision_Manager.h"

namespace Core {
    class World : public Stage{
        std::shared_ptr<Logic::Tile_Grid> grid_;
        std::shared_ptr<Logic::Collision::World_Collision_Manager> WCM_;
        std::shared_ptr<Graphics::Camera> game_camera_;

        std::unordered_map<
            std::string,
            std::shared_ptr<Logic::Model::Entity>
        > actors_models_;

        std::unordered_map<
            std::string,
            std::vector<std::shared_ptr<Graphics::View::View>>
        > actors_views_;

        std::vector<
            std::shared_ptr<Graphics::View::View>
        > gen_view_;

        public:
        World(
            const std::shared_ptr<Logic::Tile_Grid> &grid,
            const std::shared_ptr<Logic::Collision::World_Collision_Manager> &WCM,
            const std::shared_ptr<Graphics::Camera> &game_camera
            );

        ~World() override;

        void add_Actor_Model(const std::shared_ptr<Logic::Model::Entity>& actor_model);
        std::shared_ptr<Logic::Model::Entity> get_Actor_Model(const std::string& name);
        void add_Actor_View(const std::shared_ptr<Graphics::View::View> &actor_view);

        void add_entity_view(const std::shared_ptr<Graphics::View::View> &entity_view);

        std::shared_ptr<Logic::Tile_Grid> get_grid();

        void simulate(float delta) override;
        void render(sf::RenderWindow& window) override;
    };
}

#endif //PACMAN_WORLD_H