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

#include "model/grid/TileGrid.h"

#include <cmath>
#include <complex>
#include "infra/diagnostics/Logger.h"
#include "infra/math/to_Vector2.h"
#include "model/collision/HitBox_Rectangle.h"

namespace model {

    float TileGrid::tile_size() const {
        return tile_size_;
    }

    TileGrid::~TileGrid() = default;

    TileGrid::TileGrid(const infra::ast::Grid &grid_info) :
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
                    case infra::ast::Tile::Barrier:
                        tiles_[i][j] = Tile::Barrier;
                        break;
                    case infra::ast::Tile::GhostSpawn:
                        tiles_[i][j] = Tile::GhostSpawn;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    size_t TileGrid::rows() const {
        return rows_;
    }

    size_t TileGrid::columns() const {
        return columns_;
    }

    float TileGrid::width() const {
        return tile_size_ * static_cast<float>(columns_);
    }

    float TileGrid::height() const {
        return tile_size_ * static_cast<float>(rows_);
    }

    std::optional<TilePos> TileGrid::get_TilePos(const infra::math::Point2 &pos) const {
        const int cx = static_cast<int>(pos.x / tile_size_);
        const int cy = static_cast<int>(pos.y  / tile_size_);
        if (cx < 0 || cy < 0 ||
        cx >= static_cast<int>(columns_) ||
        cy >= static_cast<int>(rows_))
        {
            return std::nullopt;
        }
        return TilePos(static_cast<size_t>(cy), static_cast<size_t>(cx));
    }

    std::optional<TilePos> TileGrid::get_next_TilePos(
        const infra::math::Point2 &pos,
        const infra::math::Direction &dir) const {
        using namespace infra::math;

        int col = static_cast<int>(pos.x / tile_size());
        int row =  static_cast<int>(pos.y/ tile_size());
        //const float cx = (col + 0.5f) * tile_size();
        //const float cy = (row + 0.5f) * tile_size();

        switch (dir) {
            case Direction::Right:
                col++;
                break;
            case Direction::Left:
                col--;
                break;
            case Direction::Down:
                row++;
                break;
            case Direction::Up:
                row--;
                break;
            default:
                return std::nullopt;
        }

        return TilePos(row, col);
    }


    infra::math::Point2 TileGrid::get_next_center(
        const infra::math::Point2 &pos,
        const infra::math::Direction &dir) const {

        const int col = static_cast<int>(pos.x / tile_size_);
        const int row =  static_cast<int>(pos.y/ tile_size_);

        infra::math::Point2 center = {
            (col + 0.5f)  * tile_size_, (row + 0.5f) * tile_size_
        };

        const infra::math::Vector2 v = infra::math::to_vec(dir);
        const auto to_center = infra::math::Vector2(center - pos);
        if (to_center.dot(v) <= 0){
            center += (v * tile_size_).to_Point2();
        }

        return center;
    }


    Tile TileGrid::get_tile(const TilePos &pos) const {
        if (pos.x >= columns_ || pos.y >= rows_)
        {
            return Tile(Tile::Wall);
        }
        return tiles_[pos.y][pos.x];
    }

    infra::math::Point2 TileGrid::get_center(const TilePos &pos) const {
        const float x = (static_cast<float>(pos.x) + 0.5f)*tile_size_;
        const float y = (static_cast<float>(pos.y) + 0.5f)*tile_size_;
        return {x, y};
    }

    std::unique_ptr<collision::HitBox> TileGrid::get_hitbox(const TilePos &pos) const {
        auto center = get_center(pos);
        return std::make_unique<collision::HitBox_Rectangle>(center, tile_size_, tile_size_, 0);
    }

    void TileGrid::out_of_bounds(const TilePos &pos, const std::string &who)const {
        if (pos.x >= columns_ || pos.y >= rows_){
            throw std::out_of_range("TileGrid::"+who+" - position is out of bounds.");
        }
    }

    void TileGrid::limit(TilePos& pos) const {
        if (pos.x < 0) {
            pos.x =  0;
        }
        if (pos.x >= columns_) {
            pos.x =  columns_ - 1;
        }
        if (pos.y < 0) {
            pos.y = 0;
        }
        if (pos.y >= rows_) {
            pos.y =  rows_ - 1;
        }
    }

    bool TileGrid::can_choose_direction(
        const TilePos& pos,
        infra::math::Direction current_dir,
        Permission permission = Permission::Low
    ) const {
        int exits = 0;

        auto check = [&](infra::math::Direction dir) {
            // no turning allowed
            if (dir == infra::math::opposite(current_dir))
                return;
            // not the same value
            if (dir == current_dir)
                return;

            auto next = get_next_TilePos(get_center(pos), dir);
            if (!next.has_value())
                return;

            if (walkable(get_tile(*next), permission))
                ++exits;
        };

        check(infra::math::Direction::Up);
        check(infra::math::Direction::Down);
        check(infra::math::Direction::Left);
        check(infra::math::Direction::Right);

        // if there is at least one alternative solution, you can choose
        return exits > 0;
    }
}


