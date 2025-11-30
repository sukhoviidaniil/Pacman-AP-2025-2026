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
#include "logic/collision/HitBoxe_Shape.h"
#include <complex>

namespace Logic {
    Tile_Grid::Tile_Grid(const size_t rows, const size_t columns, const float tile_size):
    rows_(rows), columns_(columns), tile_size_(tile_size){
        // ReSharper disable once CppTemplateArgumentsCanBeDeduced
        tiles_ = std::vector<std::vector<std::shared_ptr<Tile>>>(columns_, std::vector<std::shared_ptr<Tile>>(rows_));
        for (size_t row = 0; row < rows_; row++) {
            for (size_t column = 0; column < columns_; column++) {
                const float x = static_cast<float>(row) * tile_size_;
                const float y = static_cast<float>(column) * tile_size_;
                const Math::Vector2 position = Math::Vector2(x, y);
                std::shared_ptr<Collision::HitBoxe> hb = std::make_shared<Collision::HitBoxe_Shape>(position, 1, 1);
                tiles_[row][column] = nullptr; // TODO Add Tile
            }
        }

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
            return; // You are out of this world — can be processed differently?
        }

        std::shared_ptr<Tile> newTile = tiles_[static_cast<size_t>(row)][static_cast<size_t>(col)];


        // 2. Check if there is a previous tile
        auto it = entity_tile_.find(entity);

        if (it == entity_tile_.end())
        {
            // The entity appears in the grid for the first time
            entity_tile_[entity] = newTile;
            newTile->add_Entity(entity);
            return;
        }

        std::shared_ptr<Tile> oldTile = it->second;

        // 3. If the cell has not changed, do nothing.
        if (oldTile == newTile)
            return;

        // 4. Move the object between cells
        if (oldTile)
            oldTile->remove_Entity(entity);

        newTile->add_Entity(entity);

        // 5. Update the mapping table
        it->second = newTile;
    }
}
