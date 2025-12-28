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
#include "model/grid/Tile_Grid.h"

namespace model::collision {
    class World_Collision_Manager{
    public:
        World_Collision_Manager();

        World_Collision_Manager(std::unique_ptr<Collision_Control> control, const std::shared_ptr<Tile_Grid> &world);

        [[nodiscard]] bool collision_world(const HitBox& entity) const;

        std::optional<infra::math::Vector2> collision_mtv_world(const HitBox &entity,
                                                                const infra::math::Vector2 &displacement) const;

        [[nodiscard]] std::shared_ptr<Tile_Grid> get_grid() const;

    private:
        std::unique_ptr<Collision_Control> control_;
        std::shared_ptr<Tile_Grid> grid_;
    };
}

#endif //PACMAN_WORLD_COLLISION_MANAGER_H