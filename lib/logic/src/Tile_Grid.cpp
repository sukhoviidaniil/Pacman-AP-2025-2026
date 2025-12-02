/***************************************************************
 * Project:       Pacman
 * File:          TileGrid.cpp
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

#include "logic/Tile_Grid.h"
#include <complex>

namespace Logic {
    Tile_Grid::Tile_Grid(size_t rows, size_t columns, float tile_size): rows_(rows), columns_(columns), tile_size_(tile_size) {
    }

    Tile_Grid::Tile_Grid(size_t rows, size_t columns, float tile_size, std::vector<std::vector<std::shared_ptr<Tile>>> tiles):
    rows_(rows), columns_(columns), tile_size_(tile_size), tiles_(tiles){

    }

    Tile_Grid::~Tile_Grid() = default;

    size_t Tile_Grid::get_rows() const {
        return rows_;
    }

    size_t Tile_Grid::get_columns() const {
        return columns_;
    }

    unsigned int Tile_Grid::get_width() const {
        return static_cast<unsigned int>(static_cast<float>(rows_) * tile_size_);
    }

    unsigned int Tile_Grid::get_height() const {
        return static_cast<unsigned int>(static_cast<float>(columns_) * tile_size_);
    }

    Math::Vector2 Tile_Grid::get_next_tile_center(const Math::Vector2 &pos, const Math::Vector2 &dir) const {
        const float half_ts = tile_size_ * 0.5f;
        const float W = static_cast<float>(columns_) * tile_size_;
        const float H = static_cast<float>(rows_)    * tile_size_;

        const float start_x = -W * 0.5f;
        const float start_x_center = start_x + half_ts;

        const float start_y = - H * 0.5f;
        const float start_y_center = start_y + half_ts;

        // --- 1. Знаходимо поточний індекс клітини --------------------

        const float fx = (pos.x - start_x_center) / tile_size_;   // j + (зсув всередині)
        const float fy = (pos.y - start_y_center) / tile_size_;   // i + (зсув всередині)

        int cx = static_cast<int>(std::floor(fx));
        int cy = static_cast<int>(std::floor(fy));

        if (cx < 0) cx = 0;
        if (cy < 0) cy = 0;
        if (cx >= static_cast<int>(columns_)) cx = static_cast<int>(columns_) - 1;
        if (cy >= static_cast<int>(rows_))    cy = static_cast<int>(rows_) - 1;

        // --- 2. Нульовий напрямок -------------------------------

        if (std::abs(dir.x) < 1e-6f && std::abs(dir.y) < 1e-6f){
            return {
                start_x_center + static_cast<float>(cx) * tile_size_,
                start_y_center + static_cast<float>(cy) * tile_size_
            };
        }
        int stepX = 0;
        if (dir.x > 0) {
            stepX = 1;
        }else if (dir.x < 0) {
            stepX = -1;
        }

        int stepY = 0;
        if (dir.y > 0) {
            stepY = 1;
        }else if (dir.y < 0) {
            stepY = -1;
        }

        // --- 4. Межі клітини у світових координатах -------------

        float cell_left   = start_x + static_cast<float>(cx) * tile_size_;
        float cell_right  = cell_left + tile_size_;
        float cell_bottom = start_y + static_cast<float>(cy) * tile_size_;
        float cell_top    = cell_bottom + tile_size_;

        // --- 5. Час до перетину кордонів -----------------------

        const float t_to_vert  = (stepX != 0) ? ((stepX > 0 ? cell_right : cell_left ) - pos.x) / dir.x : std::numeric_limits<float>::infinity();
        const float t_to_horiz  = (stepY != 0) ? ((stepY > 0 ? cell_top : cell_bottom) -  pos.y) / dir.y : std::numeric_limits<float>::infinity();

        // --- 6. Вибираємо найближчу стінку і рухаємо індекс --------

        float t_min = std::min(t_to_vert, t_to_horiz);
        if (t_to_vert == t_min && stepX != 0) cx += stepX;
        if (t_to_horiz == t_min && stepY != 0) cy += stepY;

        if (cx < 0) cx = 0;
        if (cy < 0) cy = 0;
        if (cx >= static_cast<int>(columns_)) cx = static_cast<int>(columns_) - 1;
        if (cy >= static_cast<int>(rows_))    cy = static_cast<int>(rows_) - 1;

        // --- 7. Центр вибраної клітини ----------------------------

        return {
            start_x_center + static_cast<float>(cx) * tile_size_,
            start_y_center + static_cast<float>(cy) * tile_size_
        };
    }

    std::vector<std::vector<std::shared_ptr<Tile>>> Tile_Grid::get_tiles() const {
        return tiles_;
    }


    std::shared_ptr<Tile> Tile_Grid::get_tile(const Math::Vector2 & position) const {
        // const Math::Vector2 m_position = position/tile_size; by base going to be 1
        // Now index_position in form like (-1.333, -2, 444)
        const double x = position.x + offset_row_;
        const double y = position.y + offset_columns_;
        // Now x and y ALWAYS >0
        const auto row = static_cast<size_t>(std::round(x));
        const auto colum = static_cast<size_t>(std::round(y));
        return get_tile(colum, row);
    }


    std::shared_ptr<Tile> Tile_Grid::get_tile(const size_t x, const size_t y) const {
        if (tiles_.empty()) return nullptr;
        if (x >= rows_ || y >= columns_) {
            throw std::out_of_range("Position is out of TileGrid");
        }
        return tiles_[y][x];
    }

    void Tile_Grid::update_Entity_Tile(const std::shared_ptr<Model::Entity> &entity) {
        if (!entity) return;
        // 1. Calculate which cell the entity falls into
        const float x = entity->get_position().x;
        const float y = entity->get_position().y;
        const int col = static_cast<int>(std::floor(x / tile_size_));
        const int row = static_cast<int>(std::floor(y / tile_size_));
        // Checking for going beyond the world
        if (row < 0 || row >= static_cast<int>(rows_) ||
            col < 0 || col >= static_cast<int>(columns_))
        {
            throw std::out_of_range("Position is out of TileGrid"); // You are out of this world — can be processed differently?
        }
        const std::shared_ptr<Tile> newTile = tiles_[static_cast<size_t>(row)][static_cast<size_t>(col)];
        // 2. Check if there is a previous tile
        const auto it = entity_tile_.find(entity);
        if (it == entity_tile_.end()){
            // The entity appears in the grid for the first time
            entity_tile_[entity] = newTile;
            newTile->add_Entity(entity);
            return;
        }
        const std::shared_ptr<Tile> oldTile = it->second;

        // 3. If the cell has not changed, do nothing.
        if (oldTile == newTile) return;

        // 4. Move the object between cells
        if (oldTile) oldTile->remove_Entity(entity);
        newTile->add_Entity(entity);
        // 5. Update the mapping table
        it->second = newTile;
    }
}
