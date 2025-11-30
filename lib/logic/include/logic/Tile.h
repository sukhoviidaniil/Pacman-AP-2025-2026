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

#include "logic/model/Terrain.h"

namespace Logic {
    class Tile {
        int status_ = 0;
        std::shared_ptr<Model::Terrain> terrain_ = nullptr;
        std::vector<std::shared_ptr<Model::Entity>> entities_;
    public:
        explicit Tile(const std::shared_ptr<Model::Terrain>& terrain);
        void set_status(int status);

        void add_Entity(const std::shared_ptr<Model::Entity> &entity);
        void remove_Entity(const std::shared_ptr<Model::Entity> &entity);

        [[nodiscard]] int get_status() const;
        [[nodiscard]] std::shared_ptr<Model::Terrain> get_terrain() const;
        [[nodiscard]] std::shared_ptr<Collision::HitBoxe> get_hitbox() const;
        [[nodiscard]] std::vector<std::shared_ptr<Model::Entity>> get_entities() const;
    };
}

#endif //PACMAN_TILE_H