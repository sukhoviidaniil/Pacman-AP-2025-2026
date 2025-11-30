/***************************************************************
 * Project:       Pacman
 * File:          Logic_Factory.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-29
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

#include "logic/Logic_Factory.h"
#include "logic/collision/HitBoxe_Shape.h"
#include <filesystem>

namespace Logic {

    std::shared_ptr<Model::Terrain> Logic_Factory::make_Terrain(
        float tile_size, const Math::Vector2 &pos, const int type) {

        auto hb = std::make_shared<Collision::HitBoxe_Shape>(pos, tile_size, tile_size, 0, 0);
        std::string name;
        unsigned int status;
        bool walkable;
        switch (type) {
            case 0:
                name = "Floor";
                status = 0;
                walkable = true;
                break;
            case 1:
                name = "Wall";
                status = 0;
                walkable = false;
                break;
            default:
                name = "Not assigned ";
                status = 999;
                walkable = false;
                break;
        }
        return std::make_shared<Model::Terrain>(name, pos, hb, status, walkable);
    }

    std::shared_ptr<Tile> Logic_Factory::make_Tile(float tile_size, const Math::Vector2 &pos, int type) {
        std::shared_ptr<Model::Terrain> terrain = make_Terrain(tile_size, pos, type);
        return std::make_shared<Tile>(terrain);
    }

    std::shared_ptr<Tile_Grid> Logic_Factory::make_grid(
        unsigned int width, unsigned int height,
        float tile_size, const std::vector<std::vector<int>> &grid) const {


    }
}
