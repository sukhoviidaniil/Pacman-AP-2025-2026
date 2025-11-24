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
#ifndef PACMAN_TILE_GRID_H
#define PACMAN_TILE_GRID_H
#include <memory>
#include <vector>

#include "Tile.h"
#include "math/Vector2.h"

namespace Logic {
    class Tile_Grid {
        size_t rows_, columns_;
        float offset_row_ = 0, offset_columns_ = 0;
        float tile_size_;

        std::vector<
            std::vector<
                std::shared_ptr<Tile>
            >
        > tiles;

        std::unordered_map<
            std::shared_ptr<Model::Entity>,
            std::shared_ptr<Tile>
        > entity_tile_;
    public:
        Tile_Grid(size_t rows, size_t columns, float tile_size);
        ~Tile_Grid();

        [[nodiscard]] size_t get_rows() const;
        [[nodiscard]] size_t get_columns() const;
        [[nodiscard]] unsigned int get_width() const;
        [[nodiscard]] unsigned int get_height() const;

        /**
         *
         * @param position Arbitrary coordinates within the coordinate grid
         * @return Tile to which the position coordinate belongs
         */
        [[nodiscard]] std::shared_ptr<Tile> get_tile(const Math::Vector2 &position) const;

        /**
         *
         * @return Tile to which the position coordinate belongs
         */
        [[nodiscard]] std::shared_ptr<Tile> get_tile(size_t x, size_t y) const;


        void update_Entity_Tile(const std::shared_ptr<Model::Entity>& entity);
    };
}


#endif //PACMAN_TILE_GRID_H