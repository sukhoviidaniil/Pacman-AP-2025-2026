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

#include "model/collision/Collision_Control.h"
#include "model/Tile_Grid.h"

namespace model::collision {
    class World_Collision_Manager{

        protected:

        void resolve_сollision(const std::shared_ptr<Entity>& entityA, const std::shared_ptr<Entity>& entityB) const;

        public:

        explicit World_Collision_Manager(const std::shared_ptr<Collision_Control> &control, const std::shared_ptr<Tile_Grid> &world);

        void calculate_collision() const;

        [[nodiscard]] bool collision_world(const std::shared_ptr<const HitBoxe>& entity) const;

        void update_Entity_Tile(const std::shared_ptr<Entity>& entity) const;

        [[nodiscard]] std::shared_ptr<const Tile_Grid> get_grid() const;

    private:
        std::shared_ptr<Collision_Control> control_;
        std::shared_ptr<Tile_Grid> grid_;
    };
}

#endif //PACMAN_WORLD_COLLISION_MANAGER_H