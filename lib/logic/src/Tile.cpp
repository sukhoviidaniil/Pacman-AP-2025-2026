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


    Tile::Tile(const std::shared_ptr<Model::Entity> &terrain) : terrain_(terrain) {

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

    std::shared_ptr<Model::Entity> Tile::get_terrain() const {
        return terrain_;
    }

    std::vector<std::shared_ptr<Model::Entity>> Tile::get_entities() const {
        return entities_;
    }
}
