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

#include <optional>

#include "model/grid/TilePos.h"
#include "infra/ast/model/Grid.h"
#include "infra/math/Direction.h"
#include "infra/math/Point2.h"
#include "model/grid/Tile.h"
#include "model/collision/HitBox.h"


namespace model {
    class TileGrid {
    public:

        ~TileGrid();

        explicit TileGrid() = default;
        explicit TileGrid(const infra::ast::Grid &grid_info);

        [[nodiscard]] float tile_size() const;
        [[nodiscard]] size_t rows() const;
        [[nodiscard]] size_t columns() const;
        [[nodiscard]] float width() const;
        [[nodiscard]] float height() const;


        [[nodiscard]] std::optional<TilePos> get_TilePos(const infra::math::Point2 &pos) const;
        [[nodiscard]] std::optional<TilePos> get_next_TilePos(const infra::math::Point2 &pos, const infra::math::Direction& dir) const;
        [[nodiscard]] infra::math::Point2 get_next_center(const infra::math::Point2& pos, const infra::math::Direction& dir) const;

        [[nodiscard]] Tile get_tile(const TilePos& pos) const;
        [[nodiscard]] infra::math::Point2 get_center(const TilePos& pos) const;
        [[nodiscard]] std::unique_ptr<collision::HitBox> get_hitbox(const TilePos& pos) const;

        void out_of_bounds(const TilePos &pos, const std::string &who) const;
        void limit(TilePos& pos) const;

        [[nodiscard]] bool can_choose_direction(
            const TilePos &pos,
            infra::math::Direction current_dir,
            Permission permission) const;

    private:

        size_t rows_ = 0, columns_ = 0;
        float tile_size_ = 0;

        std::vector<
            std::vector<
                Tile
            >
        > tiles_;
    };
}



#endif //PACMAN_TILE_GRID_H