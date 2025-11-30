/***************************************************************
 * Project:       Pacman
 * File:          World_Collision_Manager .h
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
#ifndef PACMAN_WORLD_COLLISION_MANAGER_H
#define PACMAN_WORLD_COLLISION_MANAGER_H

#include "logic/collision/Collision_Control.h"
#include "logic/Tile_Grid.h"

namespace Logic::Collision {
    class World_Collision_Manager{
        std::shared_ptr<Collision_Control> control_;
        std::shared_ptr<Tile_Grid> grid_;
        protected:

        void resolve_сollision(const std::shared_ptr<Model::Entity>& entityA, const std::shared_ptr<Model::Entity>& entityB) const;

        public:

        explicit World_Collision_Manager(const std::shared_ptr<Collision_Control> &control, const std::shared_ptr<Tile_Grid> &world);

        void calculate_collision() const;

        [[nodiscard]] bool collision_world(const std::shared_ptr<HitBoxe>& entity) const;

        void update_Entity_Tile(const std::shared_ptr<Model::Entity>& entity) const;
    };
}

#endif //PACMAN_WORLD_COLLISION_MANAGER_H