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

#include "model/grid/Tile_Grid.h"

#include <complex>
#include "infra/diagnostics/Logger.h"
#include "model/collision/HitBox_Rectangle.h"

namespace model {

    float Tile_Grid::tile_size() const {
        return tile_size_;
    }

    Tile_Grid::~Tile_Grid() = default;

    Tile_Grid::Tile_Grid(const infra::ast::Grid &grid_info) :
        rows_(grid_info.rows), columns_(grid_info.columns), tile_size_(grid_info.tile_size)
    {
        const std::vector<std::vector<infra::ast::Tile>> & grid = grid_info.grid;
        if (grid.size() != rows_) {
            const std::string err = "Grid rows doesn't match height";
            LOG(err);
            throw std::invalid_argument(err);
        }
        for (const auto &row : grid) {
            if (row.size() != columns_) {
                const std::string err = "Grid columns doesn't match width";
                LOG(err);
                throw std::invalid_argument(err);
            }
        }
        tiles_ = std::vector(rows_, std::vector<Tile>(columns_, Tile::Free));
        for (size_t i = 0 ; i < rows_; i++) {
            for (size_t j = 0 ; j < columns_; j++) {
                const infra::ast::Tile& tile = grid[i][j];
                switch (tile) {
                    case infra::ast::Tile::Wall:
                        tiles_[i][j] = Tile::Wall;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    size_t Tile_Grid::rows() const {
        return rows_;
    }

    size_t Tile_Grid::columns() const {
        return columns_;
    }

    float Tile_Grid::width() const {
        return tile_size_ * static_cast<float>(columns_);
    }

    float Tile_Grid::height() const {
        return tile_size_ * static_cast<float>(rows_);
    }

    std::optional<Tile_Grid::TilePos> Tile_Grid::get_nearest_TilePos(const infra::math::Point2 &pos) const {
        const float half_ts = tile_size_ * 0.5f;

        // const float W = static_cast<float>(columns_) * tile_size_;
        // const float H = static_cast<float>(rows_)    * tile_size_;

        const float start_x_center = half_ts;
        const float start_y_center = half_ts;

        const int cx = static_cast<int>(std::floor((pos.x - start_x_center) / tile_size_));
        const int cy = static_cast<int>(std::floor((pos.y - start_y_center) / tile_size_));

        // If outside the limits — do not return anything
        if (cx < 0 || cy < 0 ||
            cx >= static_cast<int>(columns_) ||
            cy >= static_cast<int>(rows_))
        {
            return std::nullopt;
        }

        return TilePos(static_cast<size_t>(cy), static_cast<size_t>(cx));
    }

    std::optional<Tile_Grid::TilePos> Tile_Grid::get_next_TilePos(
        const infra::math::Point2 &pos,
        const infra::math::Direction &dir) const {

        auto cur = get_nearest_TilePos(pos);
        if (!cur.has_value()) {
            return std::nullopt;
        }

        auto [y, x] = cur.value();


        int dx = 0;
        int dy = 0;
        switch (dir) {
            case infra::math::Direction::Left: dx = -1; break;
            case infra::math::Direction::Up: dy = -1; break;
            case infra::math::Direction::Down: dy = 1; break;
            case infra::math::Direction::Right: dx = 1; break;
            default:
                return std::nullopt;
        }

        const int nx = static_cast<int>(x) + dx;
        const int ny = static_cast<int>(y) + dy;
        if (nx < 0 || ny < 0 || nx >= static_cast<int>(columns_) || ny >= static_cast<int>(rows_)) {
            return std::nullopt;
        }
        return TilePos(static_cast<size_t>(ny), static_cast<size_t>(nx));
    }

    Tile Tile_Grid::get_tile_exact(const TilePos &pos) const {
        out_of_bounds(pos, "get_tile_exact");
        return tiles_[pos.y][pos.x];
    }


    std::optional<Tile> Tile_Grid::get_tile(const TilePos &pos) const {
        if (pos.x >= columns_ || pos.y >= rows_)
        {
            return std::nullopt;
        }
        return tiles_[pos.y][pos.x];
    }

    infra::math::Point2 Tile_Grid::get_center_exact(const TilePos &pos) const {
        out_of_bounds(pos, "get_center_exact");
        const float half_ts = tile_size_ * 0.5f;
        const float x = static_cast<float>(pos.x)*tile_size_ + half_ts;
        const float y = static_cast<float>(pos.y)*tile_size_ + half_ts;
        return {x, y};
    }

    std::optional<infra::math::Point2> Tile_Grid::get_center(const TilePos &pos) const {
        if (pos.x >= columns_ || pos.y >= rows_)
        {
            return std::nullopt;
        }
        const float half_ts = tile_size_ * 0.5f;
        const float x = static_cast<float>(pos.x)*tile_size_ + half_ts;
        const float y = static_cast<float>(pos.y)*tile_size_ + half_ts;
        return infra::math::Point2(x, y);
    }

    std::unique_ptr<collision::HitBox> Tile_Grid::get_hitbox(const TilePos &pos) const {
        auto center = get_center(pos);
        if (!center.has_value()) {
            return nullptr;
        }
        return std::make_unique<collision::HitBox_Rectangle>(center.value(), tile_size_, tile_size_, 0);
    }

    void Tile_Grid::out_of_bounds(const TilePos &pos, const std::string &who)const {
        if (pos.x >= columns_ || pos.y >= rows_){
            throw std::out_of_range("Tile_Grid::"+who+" - position is out of bounds.");
        }
    }
}


