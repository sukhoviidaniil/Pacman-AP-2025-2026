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

#include "logic/TileGrid.h"

#include <complex>

namespace Logic {
    TileGrid::TileGrid(const size_t t_rows, const size_t t_columns, const float t_tile_size):
    rows(t_rows), columns(t_columns), tile_size(t_tile_size){
        // ReSharper disable once CppTemplateArgumentsCanBeDeduced
        tiles = std::vector<std::vector<std::shared_ptr<Tile>>>(columns, std::vector<std::shared_ptr<Tile>>(rows));
        for (size_t row = 0; row < rows; row++) {
            for (size_t column = 0; column < columns; column++) {
                const float x = static_cast<float>(row) * tile_size;
                const float y = static_cast<float>(column) * tile_size;
                Math::Vector2 position = Math::Vector2(x, y);
                tiles[row][column] = std::make_shared<Tile>(position);
            }
        }
        offset_row = static_cast<float>(rows)/2;
        offset_column = static_cast<float>(columns)/2;
    }

    TileGrid::~TileGrid() = default;

    unsigned int TileGrid::get_width() const {
        return static_cast<unsigned int>(rows * tile_size);
    }

    unsigned int TileGrid::get_height() const {
        return static_cast<unsigned int>(columns * tile_size);
    }

    std::shared_ptr<Tile> TileGrid::get_tile(const Math::Vector2 & position) const {
        // const Math::Vector2 m_position = position/tile_size; by base going to be 1
        // Now index_position in form like (-1.333, -2, 444)
        const double x = position.x + offset_row;
        const double y = position.y + offset_column;
        // Now x and y ALWAYS >0
        const auto row = static_cast<size_t>(std::round(x));
        const auto colum = static_cast<size_t>(std::round(y));
        //
        if (row >= rows || colum >= columns) {
            throw std::out_of_range("Position is out of TileGrid");
        }
        return tiles[colum][row];
    }
}
