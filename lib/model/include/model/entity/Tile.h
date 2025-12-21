/***************************************************************
 * Project:       Pacman
 * File:          Tile.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-10-23
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
#ifndef PACMAN_TILE_H
#define PACMAN_TILE_H

#include <memory>
#include <vector>

#include "Entity.h"

namespace model::entity {
    class Tile : public Entity{
        std::vector<std::shared_ptr<Entity>> entities_;
        bool walkable_ = true;
    public:
        explicit Tile(
            std::string  name,
            const infra::math::Point2 &position,
            std::unique_ptr<collision::HitBox> hitbox,
            bool walkable
            );
        
        [[nodiscard]] bool walkable() const;

        void add_Entity(const std::shared_ptr<Entity> &entity);
        void remove_Entity(const std::shared_ptr<Entity> &entity);

        [[nodiscard]] std::vector<std::shared_ptr<Entity>> get_entities() const;
    };
}

#endif //PACMAN_TILE_H