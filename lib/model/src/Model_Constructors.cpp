/***************************************************************
 * Project:       Pacman
 * File:          Model_Constructors.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-25
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

#include "model/Model.h"
#include "model/collision/HitBox_Rectangle.h"
#include "model/collision/Separating_Axis_Theorem.h"

namespace model {

    Model::Model(const infra::ast::Model &m, const unsigned int& level) {
        grid_ = std::make_shared<Tile_Grid>(m.grid);
        auto sat = std::make_unique<collision::Separating_Axis_Theorem>();
        wcm_ = collision::World_Collision_Manager(std::move(sat), grid_);

        const std::vector<std::vector<infra::ast::Tile>>& s_grid = m.grid.grid;
        const unsigned int rows = m.grid.rows;
        const unsigned int columns = m.grid.columns;

        for (unsigned int y = 0; y < rows; ++y) {
            for (unsigned int x = 0; x < columns; ++x) {
                const infra::ast::Tile& in_cell = s_grid[y][x];
                std::shared_ptr<const entity::Tile> tile = grid_->get_tile(y, x);
                if (tile == nullptr) continue;
                infra::math::Point2 position = tile->position();
                process_tile(m, level, in_cell, position);
            }
        }
    }

    Model::Model(
        const infra::ast::Model &m, const unsigned int &level,
        std::vector<std::shared_ptr<entity::Coin>> coins
    ) {
        grid_ = std::make_shared<Tile_Grid>(m.grid);
        auto sat = std::make_unique<collision::Separating_Axis_Theorem>();
        wcm_ = collision::World_Collision_Manager(std::move(sat), grid_);

        const std::vector<std::vector<infra::ast::Tile>>& s_grid = m.grid.grid;
        const unsigned int rows = m.grid.rows;
        const unsigned int columns = m.grid.columns;

        for (unsigned int y = 0; y < rows; ++y) {
            for (unsigned int x = 0; x < columns; ++x) {
                const infra::ast::Tile& in_cell = s_grid[y][x];
                std::shared_ptr<const entity::Tile> tile = grid_->get_tile(y, x);
                if (tile == nullptr) continue;
                infra::math::Point2 position = tile->position();
                process_tile_without_coins(m, level, in_cell, position);
            }
        }

        coins_ = std::move(coins);
    }

    bool Model::process_tile(
        const infra::ast::Model &m,
        const unsigned int &level,
        const infra::ast::Tile &in_cell,
        const infra::math::Point2 &position
    ) {
        switch (in_cell) {
            case infra::ast::Tile::PacmanSpawn: {
                float size = m.pacman_spawn.size;
                float speed = m.pacman_spawn.speed;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, size, size, 0);
                pacman_ = std::make_shared<entity::Pacman>(position, std::move(h), speed);
                return true;
            }
            default:
                return false;
        }
    }

    void Model::process_tile_without_coins(
        const infra::ast::Model &m,
        const unsigned int &level,
        const infra::ast::Tile& in_cell,
        const infra::math::Point2& position
        ) {

        if (process_tile(m, level, in_cell, position)) {
            return;
        }
        // TODO
    }
}
