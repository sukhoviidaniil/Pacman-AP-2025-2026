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
#include "logic/model/Actor.h"
#include <filesystem>

namespace Logic {

    std::shared_ptr<Model::Terrain> Logic_Factory::make_Terrain(
        float tile_size, const Math::Vector2 &pos, const int type) {

        auto hb = std::make_shared<Collision::HitBoxe_Shape>(pos, tile_size, tile_size, 0, 0);
        std::string name;
        unsigned int max_status;
        bool walkable;
        switch (type) {
            case 0:
                name = "Floor";
                max_status = 1;
                walkable = true;
                break;
            case 1:
                name = "Wall";
                max_status = 1;
                walkable = false;
                break;
            default:
                name = "Not assigned ";
                max_status = 999;
                walkable = false;
                break;
        }
        return std::make_shared<Model::Terrain>(name, pos, hb, max_status, walkable);
    }

    std::shared_ptr<Tile> Logic_Factory::make_Tile(float tile_size, const Math::Vector2 &pos, int type) {
        std::shared_ptr<Model::Terrain> terrain = make_Terrain(tile_size, pos, type);
        return std::make_shared<Tile>(terrain);
    }

    std::shared_ptr<Collision::HitBoxe> Logic_Factory::make_HitBox(const Collision::HitBoxe_Shape_Info &info) {
        return std::make_shared<Collision::HitBoxe_Shape>(info.pos, info.height, info.width, info.layer, info.strength);
    }

    std::shared_ptr<Model::Entity> Logic_Factory::make_Actor(Model::Actor_Info info) {
        std::shared_ptr<Model::Entity> a = std::make_shared<Model::Actor>(
            info.name,
            info.position,
            info.hitbox,
            info.max_status,
            info.current_direction,
            info.speed
            );
        return a;
    }

    std::shared_ptr<Tile_Grid> Logic_Factory::make_grid(const Tile_Grid_Info &tile_grid_info){
        unsigned int rows = tile_grid_info.rows;
        unsigned int columns = tile_grid_info.columns;
        float tile_size = tile_grid_info.tile_size;
        const std::vector<std::vector<int>>& grid = tile_grid_info.logic_grid;

        if (grid.empty()) throw std::invalid_argument("Grid is empty");
        if (grid.size() != rows) throw std::invalid_argument("Grid rows doesn't match height");
        for (const auto &row : grid) {
            if (row.empty()) throw std::invalid_argument("Grid is empty");
            if (row.size() != columns) throw std::invalid_argument("Grid columns doesn't match width");
        }

        // ReSharper disable once CppTemplateArgumentsCanBeDeduced
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles(rows, std::vector<std::shared_ptr<Tile>>(columns, nullptr));

        const float half_tile_size = tile_size * 0.5f;
        const float height_size = static_cast<float>(rows) * tile_size;
        const float width_size = static_cast<float>(columns) * tile_size;

        // Coordinates of the center of the tile in the upper left corner of the grid
        const float start_x = - width_size*0.5f + half_tile_size;
        const float start_y = height_size*0.5f - half_tile_size;
        for (size_t i = 0 ; i < rows; i++) {
            float y = start_y - tile_size * static_cast<float>(i);
            for (size_t j = 0 ; j < columns; j++) {
                float x = start_x + tile_size * static_cast<float>(j);
                Math::Vector2 p(x, y);
                tiles[i][j] = make_Tile(tile_size, p, grid[i][j]);
            }
        }
        return std::make_shared<Tile_Grid>(rows, columns, tile_size, tiles);
    }
}
