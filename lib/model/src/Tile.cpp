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

#include "model/Tile.h"

namespace model {

    Tile::Tile(bool walkable) : walkable_(walkable) {
    }

    bool Tile::walkable() const {
        return walkable_;
    }

    void Tile::add_Entity(const std::shared_ptr<Entity> &entity) {
        if (!entity) return;

        for (const auto& e : entities_) {
            if (e == entity)
                return;
        }

        entities_.push_back(entity);
    }

    void Tile::remove_Entity(const std::shared_ptr<Entity> &entity) {
        if (!entity) return;

        for (auto it = entities_.begin(); it != entities_.end(); ++it) {
            if (*it == entity) {
                entities_.erase(it);
                return;
            }
        }
    }

    std::vector<std::shared_ptr<Entity>> Tile::get_entities() const {
        return entities_;
    }
}
