/***************************************************************
 * Project:       Pacman
 * File:          Model.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-18
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
        create_model(m, level);

    }

    Model::Model(
        const infra::ast::Model &m, const unsigned int &level,
        const std::vector<std::shared_ptr<entity::Coin>> &coins
        ) {
        create_model(m, level, coins);
    }


    bool Model::all_coins_eaten() const {
        return coins.empty();
    }


    void Model::run(const float delta) {

    }


    std::shared_ptr<entity::Pacman> Model::get_pacman() const {
        return pacman;
    }


    void Model::create_model(const infra::ast::Model &m, const unsigned int &level) {

        grid = std::make_shared<Tile_Grid>(m.grid);
        auto sat = std::make_unique<collision::Separating_Axis_Theorem>();
        wcm_ = collision::World_Collision_Manager(std::move(sat), grid);

        const std::vector<std::vector<infra::ast::Tile>>& s_grid = m.grid.grid;
        const unsigned int rows = m.grid.rows;
        const unsigned int columns = m.grid.columns;

        for (unsigned int y = 0; y < rows; ++y) {
            for (unsigned int x = 0; x < columns; ++x) {
                const infra::ast::Tile& in_cell = s_grid[y][x];
                std::shared_ptr<const entity::Tile> tile = grid->get_tile(y, x);
                if (tile == nullptr) continue;
                infra::math::Point2 position = tile->position();
                switch (in_cell) {
                    case infra::ast::Tile::PacmanSpawn: {
                        float size = m.pacman_spawn.size;
                        float speed = m.pacman_spawn.speed;
                        auto h = std::make_unique<collision::HitBox_Rectangle>(position, size, size, 0);
                        pacman = std::make_shared<entity::Pacman>(position, std::move(h), speed);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }

    void Model::create_model(const infra::ast::Model &m, const unsigned int &level,
        std::vector<std::shared_ptr<entity::Coin>>) {
    }
}
