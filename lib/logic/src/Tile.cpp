/***************************************************************
 * Project:       Pacman
 * File:          Tile.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-05
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

#include "logic/Tile.h"

namespace Logic {

    Tile::Tile(const std::shared_ptr<Model::Terrain> &terrain):
    terrain_(terrain){

    }

    void Tile::set_status(int status) {
        status_ = status;
    }

    void Tile::add_Entity(const std::shared_ptr<Model::Entity> &entity) {
        if (!entity) return;

        for (const auto& e : entities_) {
            if (e == entity)
                return;
        }

        entities_.push_back(entity);
    }

    void Tile::remove_Entity(const std::shared_ptr<Model::Entity> &entity) {
        if (!entity) return;

        for (auto it = entities_.begin(); it != entities_.end(); ++it) {
            if (*it == entity) {
                entities_.erase(it);
                return;
            }
        }
    }

    int Tile::get_status() const {
        return status_;
    }

    std::shared_ptr<Model::Terrain> Tile::get_terrain() const {
        return terrain_;
    }

    std::shared_ptr<Collision::HitBoxe> Tile::get_hitbox() const {
        if (terrain_ == nullptr) return nullptr;
        return terrain_->get_hitboxe();
    }

    std::vector<std::shared_ptr<Model::Entity>> Tile::get_entities() const {
        return entities_;
    }
}
