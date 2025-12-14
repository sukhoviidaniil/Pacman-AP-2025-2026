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

#include "model/Tile_Grid.h"
#include "model/Entity.h"
#include <complex>
#include <utility>

#include "model/collision/HitBox_Rectangle.h"

namespace model {

    Tile_Grid::Tile_Grid(const size_t rows, const size_t columns, const float tile_size, std::vector<std::vector<std::shared_ptr<Tile>>> tiles):
    rows_(rows), columns_(columns), tile_size_(tile_size), tiles_(std::move(tiles)){

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

    std::shared_ptr<const Tile> Tile_Grid::get_tile(const size_t &x, const size_t &y) const {
        if (x >= columns_ || y >= rows_)
        {
            return nullptr;
        }
        return tiles_[y][x];
    }

    std::optional<math::Point2> Tile_Grid::get_tile_center(const size_t &x, const size_t &y) const {
        if (x >= columns_ || y >= rows_)
            return std::nullopt;

        const float half_ts = tile_size_ * 0.5f;

        const float W = static_cast<float>(columns_) * tile_size_;
        const float H = static_cast<float>(rows_)    * tile_size_;

        const float start_x_center = -W * 0.5f + half_ts;
        const float start_y_center = -H * 0.5f + half_ts;

        return math::Point2{
            start_x_center + static_cast<float>(x) * tile_size_,
            start_y_center + static_cast<float>(y) * tile_size_
        };
    }

    std::shared_ptr<const collision::HitBoxe> Tile_Grid::get_tile_hitboxe(const size_t &x, const size_t &y) const {
        std::shared_ptr<const Tile> tile = get_tile(x, y);
        if (!tile) return nullptr;
        std::optional<math::Point2> t = get_tile_center(x, y);
        if (!t) return nullptr;
        const math::Point2& tile_center = t.value();
        std::shared_ptr<const collision::HitBox_Rectangle> hb = std::make_shared<collision::HitBox_Rectangle>(tile_center, tile_size_, tile_size_, tile->walkable());
        return hb;
    }

    std::shared_ptr<const Tile> Tile_Grid::get_nearest_tile(const math::Point2 &pos) const {
        std::optional<std::pair<size_t, size_t>> res = get_nearest_tile_size_t(pos);
        if (res.has_value()) {
            auto [x, y] = res.value();
            return tiles_[x][y];
        }
        return nullptr;
    }

    std::optional<std::pair<size_t, size_t>> Tile_Grid::get_nearest_tile_size_t(const math::Point2 &pos) const {
        const float half_ts = tile_size_ * 0.5f;

        const float W = static_cast<float>(columns_) * tile_size_;
        const float H = static_cast<float>(rows_)    * tile_size_;

        const float start_x_center = -W * 0.5f + half_ts;
        const float start_y_center = -H * 0.5f + half_ts;

        const int cx = static_cast<int>(std::round((pos.x - start_x_center) / tile_size_));
        const int cy = static_cast<int>(std::round((pos.y - start_y_center) / tile_size_));

        // If outside the limits — do not return anything
        if (cx < 0 || cy < 0 ||
            cx >= static_cast<int>(columns_) ||
            cy >= static_cast<int>(rows_))
        {
            return std::nullopt;
        }

        return std::pair{
            static_cast<size_t>(cx),
            static_cast<size_t>(cy)
        };
    }

    std::shared_ptr<const Tile> Tile_Grid::get_next_tile(const math::Point2 &pos, const math::Vector2 &dir) const {
        auto cur = get_nearest_tile_size_t(pos);
        if (!cur)
            return nullptr;

        auto [x, y] = *cur;

        const int dx = (dir.x > 0.f) - (dir.x < 0.f);
        const int dy = (dir.y > 0.f) - (dir.y < 0.f);

        // No direction — no next tile
        if (dx == 0 && dy == 0)
            return nullptr;

        const int nx = static_cast<int>(x) + dx;
        const int ny = static_cast<int>(y) + dy;

        if (nx < 0 || ny < 0 ||
            nx >= static_cast<int>(columns_) ||
            ny >= static_cast<int>(rows_))
        {
            return nullptr;
        }

        return tiles_[static_cast<size_t>(ny)][static_cast<size_t>(nx)];
    }

    std::optional<math::Point2> Tile_Grid::get_next_center(const math::Point2 &pos, const math::Vector2 &dir) const {
        auto cur = get_nearest_tile_size_t(pos);
        if (!cur) return std::nullopt;

        auto [x, y] = *cur;
        const int dx = (dir.x > 0.f) - (dir.x < 0.f);
        const int dy = (dir.y > 0.f) - (dir.y < 0.f);
        if (dx == 0 && dy == 0) return std::nullopt;

        const int nx = static_cast<int>(x) + dx;
        const int ny = static_cast<int>(y) + dy;
        if (nx < 0 || ny < 0 ||
            nx >= static_cast<int>(columns_) ||
            ny >= static_cast<int>(rows_))
        {
            return std::nullopt;
        }

        const float half_ts = tile_size_ * 0.5f;
        const float W = static_cast<float>(columns_) * tile_size_;
        const float H = static_cast<float>(rows_)    * tile_size_;
        const float start_x_center = -W * 0.5f + half_ts;
        const float start_y_center = -H * 0.5f + half_ts;

        math::Point2 result = {
            start_x_center + static_cast<float>(nx) * tile_size_,
            start_y_center + static_cast<float>(ny) * tile_size_
        };
        return result;
    }

    std::vector<std::vector<std::shared_ptr<const Tile>>> Tile_Grid::get_tiles() const {
        std::vector<std::vector<std::shared_ptr<const Tile>>> result;
        result.reserve(tiles_.size());

        for (const auto& row : tiles_) {
            std::vector<std::shared_ptr<const Tile>> newRow;
            newRow.reserve(row.size());

            for (const auto& tile : row) {
                newRow.emplace_back(std::const_pointer_cast<const Tile>(tile));
                // або просто: newRow.emplace_back(tile);
            }

            result.emplace_back(std::move(newRow));
        }
        return result;
    }


    void Tile_Grid::update_Entity_Tile(const std::shared_ptr<Entity> &entity) {
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


