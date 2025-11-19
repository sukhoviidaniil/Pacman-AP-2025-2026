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
    Tile_Grid::Tile_Grid(const size_t t_rows, const size_t t_columns, const float t_tile_size):
    rows_(t_rows), columns_(t_columns), tile_size_(t_tile_size){
        // ReSharper disable once CppTemplateArgumentsCanBeDeduced
        tiles = std::vector<std::vector<std::shared_ptr<Tile>>>(columns_, std::vector<std::shared_ptr<Tile>>(rows));
        for (size_t row = 0; row < rows_; row++) {
            for (size_t column = 0; column < columns_; column++) {
                const float x = static_cast<float>(row) * tile_size_;
                const float y = static_cast<float>(column) * tile_size_;
                Math::Vector2 position = Math::Vector2(x, y);
                tiles[row][column] = std::make_shared<Tile>(position);
            }
        }

    }

    Tile_Grid::~Tile_Grid() = default;

    unsigned int Tile_Grid::get_width() const {
        return static_cast<unsigned int>(rows_ * tile_size_);
    }

    unsigned int Tile_Grid::get_height() const {
        return static_cast<unsigned int>(columns_ * tile_size_);
    }


    std::shared_ptr<Tile> Tile_Grid::get_tile(const Math::Vector2 & position) const {
        /*
        // const Math::Vector2 m_position = position/tile_size; by base going to be 1
        // Now index_position in form like (-1.333, -2, 444)
        const double x = position.x + offset_row_;
        const double y = position.y + offset_column_;
        // Now x and y ALWAYS >0
        const auto row = static_cast<size_t>(std::round(x));
        const auto colum = static_cast<size_t>(std::round(y));
        //
        if (row >= rows || colum >= columns) {
            throw std::out_of_range("Position is out of TileGrid");
        }
        return tiles[colum][row];
        */
        throw;
    }


    std::shared_ptr<Tile> Tile_Grid::get_tile(size_t x, size_t y) const {
        if (x >= rows_ || y >= columns_) {
            throw std::out_of_range("Position is out of TileGrid");
        }
        return tiles[y][x];

    }
}
