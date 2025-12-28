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
#include "model/entity/PowerPellet.h"

namespace model {

    Model::Model(const infra::ast::Model &m, const unsigned int& level) {
        grid_ = std::make_shared<Tile_Grid>(m.grid);
        auto sat = std::make_unique<collision::Separating_Axis_Theorem>();
        wcm_ = collision::World_Collision_Manager(std::move(sat), grid_);

        const std::vector<std::vector<infra::ast::Tile>>& s_grid = m.grid.grid;
        const size_t rows = m.grid.rows;
        const size_t columns = m.grid.columns;

        for (size_t y = 0; y < rows; ++y) {
            for (size_t x = 0; x < columns; ++x) {
                const infra::ast::Tile& in_cell = s_grid[y][x];
                std::optional<infra::math::Point2> center = grid_->get_center(Tile_Grid::TilePos(y,x));
                if (!center.has_value()) {
                    continue;
                }
                infra::math::Point2 position = center.value();
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
        const size_t rows = m.grid.rows;
        const size_t columns = m.grid.columns;

        for (size_t y = 0; y < rows; ++y) {
            for (size_t x = 0; x < columns; ++x) {
                const infra::ast::Tile& in_cell = s_grid[y][x];
                std::optional<infra::math::Point2> center = grid_->get_center(Tile_Grid::TilePos(y,x));
                if (!center.has_value()) {
                    continue;
                }
                infra::math::Point2 position = center.value();
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
                float size = m.grid.tile_size;
                float speed = m.pacman_spawn.speed;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, size, size, 0);
                pacman_ = std::make_shared<entity::Pacman>(size, position, std::move(h), speed);
                return true;
            }
            case infra::ast::Tile::CoinSpawn: {
                float size = m.coin_spawn.size;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, size, size, 0);
                coins_.push_back(std::make_shared<entity::Coin>(size, position, std::move(h)));
                return true;
            }
            case infra::ast::Tile::PowerPelletSpawn: {
                std::string name = m.power_pellet_spawn.name;
                float size = m.power_pellet_spawn.size;
                float buff_duration = m.power_pellet_spawn.buff_duration;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, size, size, 0);
                power_pellets_.push_back(
                    std::make_shared<entity::PowerPellet>(name, size, position, std::move(h), buff_duration)
                    );
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
