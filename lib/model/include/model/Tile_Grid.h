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

#include "entity/Tile.h"

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include "infra/ast/model/Grid.h"

namespace model {
    class Tile_Grid {
    public:
        ~Tile_Grid();

        explicit Tile_Grid(const infra::ast::Grid &grid_info);
        Tile_Grid(size_t rows, size_t columns, float tile_size, std::vector<std::vector<std::shared_ptr<entity::Tile>>> tiles);

        float tile_size() const;
        [[nodiscard]] size_t get_rows() const;
        [[nodiscard]] size_t get_columns() const;
        [[nodiscard]] float get_width() const;
        [[nodiscard]] float get_height() const;

        std::shared_ptr<const entity::Tile> get_tile(const size_t& y, const size_t& x) const;
        std::optional<std::pair<size_t, size_t>> get_nearest_tile_size_t(const infra::math::Point2 &pos) const;
        /**
         *
         * @param pos Arbitrary coordinates within the coordinate grid
         * @return Tile to which the position coordinate belongs
         */
        [[nodiscard]] std::shared_ptr<const entity::Tile> get_nearest_tile(const infra::math::Point2 &pos) const;


        [[nodiscard]] std::shared_ptr<const entity::Tile> get_next_tile(const infra::math::Point2& pos, const infra::math::Vector2& dir) const;

        [[nodiscard]] std::vector<std::vector<std::shared_ptr<const entity::Tile>>> get_tiles() const;

        /** Видаляє Сутність зі старої клітинки та додає її до нової, використовуючи її позицію
         *
         * @param entity
         */
        void update_Entity_Tile(const std::shared_ptr<Entity>& entity);
    private:

        size_t rows_, columns_;
        float tile_size_;

        std::vector<
            std::vector<
                std::shared_ptr<entity::Tile>
            >
        > tiles_;

        std::unordered_map<
            std::shared_ptr<Entity>,
            std::shared_ptr<entity::Tile>
        > entity_tile_;
    };
}


#endif //PACMAN_TILE_GRID_H