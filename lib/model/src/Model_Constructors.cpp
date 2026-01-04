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
#include "model/ai/GhostAI.h"
#include "model/ai/path_finder/PF_Factory.h"
#include "model/ai/target_strategy/TS_Factory.h"
#include "model/collision/HitBox_Rectangle.h"
#include "model/collision/Separating_Axis_Theorem.h"
#include "model/entity/PowerPellet.h"

namespace model {
    namespace ai {
        enum class GhostRole;
    }

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
        start_wait_ += 1.f;
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
                float hb_size = m.coin_spawn.hitbox_size;
                float sp_size = m.coin_spawn.sprite_size;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, hb_size, hb_size, 0);
                coins_.push_back(std::make_shared<entity::Coin>(sp_size, position, std::move(h)));
                break;
            }
            case infra::ast::Tile::PowerPelletSpawn: {
                std::string name = m.power_pellet_spawn.name;
                float hb_size = m.power_pellet_spawn.hitbox_size;
                float sp_size = m.power_pellet_spawn.sprite_size;
                float buff_duration = m.power_pellet_spawn.buff_duration;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, hb_size, hb_size, 0);
                power_pellets_.push_back(
                    std::make_shared<entity::PowerPellet>(name, sp_size, position, std::move(h), buff_duration)
                    );
                break;
            }
            default: break;
        }
    }

    void Model::make_Ghosts(
        const ai::GhostRole& role,
        float hb_size,
        const infra::math::Point2 &position,
        const unsigned int &level,
        const infra::ast::GhostInfo& info
        ) {

        float sp_size = info.sprite_size;
        const float amount_per_level = info.amount_per_level;
        const int amount = info.start_amount + static_cast<int>(amount_per_level * level);
        float base_speed = info.base_speed  + info.base_speed * level;
        float frightened_speed = info.frightened_speed + info.frightened_speed_inc * level;
        float eaten_speed = info.eaten_speed;

        const std::optional<TilePos> t_pos = grid_.get_TilePos(position);
        if (!t_pos.has_value()) return;
        const TilePos home_pos = t_pos.value();
        for (int index = 0; index < amount; index++) {
            std::unique_ptr<ai::TargetStrategy> chase_target = ai::TS_Factory::make(role);
            std::unique_ptr<ai::TargetStrategy> scatter_target = ai::TS_Factory::make_corner(grid_, infra::math::Direction::Any);

            std::unique_ptr<ai::IPathFinder> move_policy =ai::PF_Factory::make(info.path_finder);

            ai::GhostAI ai(home_pos, std::move(chase_target), std::move(scatter_target), std::move(move_policy));

            auto h = std::make_unique<collision::HitBox_Rectangle>(position, hb_size, hb_size, 0);
            auto ghost = std::make_shared<entity::Ghost>(
                role,
                sp_size,
                position,
                std::move(h),
                base_speed,
                frightened_speed,
                eaten_speed,
                std::move(ai),
                index);

            ghosts_.push_back(ghost);
            if (role == ai::GhostRole::Blinky) {
                blinkys_.push_back(ghost);
            }
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
                float hb_size = m.grid.tile_size;
                float sp_size = m.pacman_spawn.sprite_size;
                float speed = m.pacman_spawn.speed;
                auto h = std::make_unique<collision::HitBox_Rectangle>(position, hb_size, hb_size, 0);
                pacman_ = std::make_shared<entity::Pacman>(sp_size, position, std::move(h), speed);
                return true;
            }
            case infra::ast::Tile::GhostSpawn: {
                const float hb_size = m.grid.tile_size;
                make_Ghosts(ai::GhostRole::Blinky, hb_size, position, level, m.ghost_spawn.Blinky);
                make_Ghosts(ai::GhostRole::Inky, hb_size, position, level, m.ghost_spawn.Inky);
                make_Ghosts(ai::GhostRole::Clyde, hb_size, position, level, m.ghost_spawn.Clyde);
                make_Ghosts(ai::GhostRole::Pinky, hb_size, position, level, m.ghost_spawn.Pinky);
                return true;
            }
            default:
                return false;
        }
    }
}
