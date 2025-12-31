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

    Model::Model(
        const infra::ast::Model &m,
        const std::shared_ptr<infra::Score> &score,
        std::unique_ptr<collision::Collision_Control> cc,
        std::vector<std::shared_ptr<entity::Coin>> coins,
        std::vector<std::shared_ptr<entity::PowerPellet>> power_pellets
        ) :  grid_(m.grid), collision_control_(std::move(cc)), score_(score)  {

        bool consumables_emty = coins.empty() && power_pellets.empty();

        if (!consumables_emty) {
            power_pellets_ = std::move(power_pellets);
            coins_ = std::move(coins);
        }

        const std::vector<std::vector<infra::ast::Tile>>& s_grid = m.grid.grid;
        const size_t rows = m.grid.rows;
        const size_t columns = m.grid.columns;

        for (size_t y = 0; y < rows; ++y) {
            for (size_t x = 0; x < columns; ++x) {
                const infra::ast::Tile& in_cell = s_grid[y][x];
                infra::math::Point2 center = grid_.get_center(TilePos(y,x));

                if (consumables_emty) {
                    process_tile(m, score_->level(), in_cell, center);
                }else {
                    process_tile_without_consumables(m, score_->level(), in_cell, center);
                }
            }
        }

    }

    void Model::add_wait() {
        wait_ += 1.f;
    }


    void Model::process_tile(
        const infra::ast::Model &m,
        const unsigned int &level,
        const infra::ast::Tile &in_cell,
        const infra::math::Point2 &position
    ) {

        if (process_tile_without_consumables(m, level, in_cell, position)) {
            return;
        }
        switch (in_cell) {
            case infra::ast::Tile::CoinSpawn: {
                float size = m.coin_spawn.size;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, size, size, 0);
                coins_.push_back(std::make_shared<entity::Coin>(size, position, std::move(h)));
                break;
            }
            case infra::ast::Tile::PowerPelletSpawn: {
                std::string name = m.power_pellet_spawn.name;
                float size = m.power_pellet_spawn.size;
                float buff_duration = m.power_pellet_spawn.buff_duration;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, size, size, 0);
                power_pellets_.push_back(
                    std::make_shared<entity::PowerPellet>(name, size, position, std::move(h), buff_duration)
                    );
                break;
            }
            default: break;
        }
    }

    bool Model::process_tile_without_consumables(
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

            default:
                return false;
        }

        // TODO
    }
}
