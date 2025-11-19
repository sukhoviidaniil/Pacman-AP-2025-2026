/***************************************************************
 * Project:       Pacman
 * File:          TileGrid.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-04
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
#ifndef PACMAN_TILEGRID_H
#define PACMAN_TILEGRID_H
#include <memory>
#include <vector>

#include "Tile.h"
#include "math/Vector2.h"

namespace Logic {
    class TileGrid {
        size_t rows, columns;
        float tile_size;
        std::vector<
            std::vector<
                std::shared_ptr<Tile>
            >
        > tiles;
        float offset_row, offset_column;
    public:
        TileGrid(size_t rows, size_t columns, float tile_size);
        ~TileGrid();
        [[nodiscard]] unsigned int get_width() const;
        [[nodiscard]] unsigned int get_height() const;
        /**
         *
         * @param position Arbitrary coordinates within the coordinate grid
         * @return Tile to which the position coordinate belongs
         */
        [[nodiscard]] std::shared_ptr<Tile> get_tile(const Math::Vector2 &position) const;
    };
}


#endif //PACMAN_TILEGRID_H