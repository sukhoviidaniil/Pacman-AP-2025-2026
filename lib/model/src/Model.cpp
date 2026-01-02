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

#include <iostream>

#include "infra/diagnostics/Logger.h"
#include "infra/event/events/game.h"


namespace model {

    bool Model::all_coins_collected() const {
        return coins_.empty();
    }


    void Model::run(const float delta) {
        // 0.
        if (start_wait_ > 0) {
            start_wait_ -= delta;
            return;
        }
        if (pacman_->has_buff()) {
            pacman_->elapsed(delta);
        }
        if (pacman_status_ == infra::Status::Dead) {
            if (death_wait_ > 0) {
                death_wait_ -= delta;
                return;
            }else {
                const auto a = std::make_unique<infra::event::EventInstance<infra::event::game::PacMan_Died>>(infra::event::game::PacMan_Died());
                event_store_.push_concept(*a);
                return;
            }
        }


        // 1. Updating timers and modes
        score_->run(delta);

        // 3. Move the packman
        pacman_->move(delta, grid_);
        std::optional<TilePos> t = grid_.get_TilePos(pacman_->position());
        if (!t.has_value()) {
            std::string err = "Pacman is outside the grid ";
            throw std::runtime_error(err);
        }
        const TilePos pacman_pos = t.value();

        // 4. Move all ghosts
        {
            std::vector<TilePos> blinky_positions;
            blinky_positions.reserve(blinkys_.size());
            for (const auto& ghost : blinkys_) {
                std::optional<TilePos> tt = grid_.get_TilePos(pacman_->position());
                if (!tt.has_value()) continue;
                blinky_positions.push_back(tt.value());

            }

            std::span<const TilePos> blinky_span(blinky_positions);
            ai::GlobalGhostContext g_cts{
                .map = grid_,
                .pacman_pos = pacman_pos,
                .buff_duration = pacman_->buff_time(),
                .pacman_direction = pacman_->get_direction(),
                .blinky_positions = blinky_span
            };
            for (const auto& ghost : ghosts_) {
                ghost->act(delta, g_cts);
            }
        }

        // 5.
        // search for all coins and power_pellets in the tiles nearby pacman
        // try to colect
        {
            // Coins
            const std::vector<std::shared_ptr<entity::Coin>> near = get_coins_near(pacman_pos);
            std::vector<std::shared_ptr<entity::Coin>> to_remove;
            for (const auto& coin : near) {
                if (collision_control_->collision(pacman_->hitboxe(), coin->hitboxe())) {
                    unsigned int added_score = score_->coin_collection();
                    to_remove.push_back(coin);
                }
            }
            for (const auto& coin : to_remove) {
                std::erase(coins_, coin);
            }
        }
        {
            // Power Pellets
            const std::vector<std::shared_ptr<entity::PowerPellet>> near = get_power_pellets_near(pacman_pos);
            std::vector<std::shared_ptr<entity::PowerPellet>> to_remove;
            for (const auto& pp : near) {
                if (collision_control_->collision(pacman_->hitboxe(), pp->hitboxe())) {
                    pacman_->take_buff(pp->buff_duration());
                    for (const auto& ghost : ghosts_) {
                        ghost->weak();
                    }
                    to_remove.push_back(pp);
                }
            }
            for (const auto& pp : to_remove) {
                std::erase(power_pellets_, pp);
            }
        }


        // 6.
        // search for all ghosts in the tiles nearby pacman
        // try to collide
        {
            const std::vector<std::shared_ptr<entity::Ghost>> near = get_ghosts_near(pacman_pos);
            for (const auto& ghost : near) {
                if (collision_control_->collision(pacman_->hitboxe(), ghost->hitboxe())) {
                    if (pacman_->has_buff()) {
                        // TODO

                    }else {
                        pacman_status_ = infra::Status::Dead;
                        break;
                    }
                }
            }
        }

        // 7.
        // Check for level completion
        if (coins_.empty()) {
            const auto a = std::make_unique<infra::event::EventInstance<infra::event::game::All_Coins_Collected>>(infra::event::game::All_Coins_Collected());
            event_store_.push_concept(*a);
        }
    }

    std::shared_ptr<entity::Pacman> Model::get_pacman() const {
        return pacman_;
    }

    infra::Status Model::pacman_status() const {
        return pacman_status_;
    }


    std::vector<std::shared_ptr<entity::Coin>> Model::get_coins_near(const TilePos &pos) const {
        std::vector<std::shared_ptr<entity::Coin>> result;
        for (const auto& coin : coins_) {
            std::optional<TilePos> t = grid_.get_TilePos(coin->position());
            if (!t.has_value()) continue;
            TilePos coin_pos = t.value();
            if (are_close(pos, coin_pos)) {
                result.push_back(coin);
            }
        }
        return result;
    }

    std::vector<std::shared_ptr<entity::PowerPellet>> Model::get_power_pellets_near(const TilePos &pos) const {
        std::vector<std::shared_ptr<entity::PowerPellet>> result;
        for (const auto& pp : power_pellets_) {
            std::optional<TilePos> t = grid_.get_TilePos(pp->position());
            if (!t.has_value()) continue;
            TilePos pp_pos = t.value();
            if (are_close(pos, pp_pos)) {
                result.push_back(pp);
            }
        }
        return result;
    }

    std::vector<std::shared_ptr<entity::Ghost>> Model::get_ghosts_near(const TilePos &pos) const {
        std::vector<std::shared_ptr<entity::Ghost>> result;
        for (const auto& ghost : ghosts_) {
            std::optional<TilePos> t = grid_.get_TilePos(ghost->position());
            if (t.has_value()) continue;
            TilePos ghost_pos = t.value();
            if (are_close(pos, ghost_pos)) {
                result.push_back(ghost);
            }
        }
        return result;
    }

    void Model::remove_coin(const std::shared_ptr<entity::Coin>& coin_to_remove) {
        std::erase(coins_, coin_to_remove);
    }

    void Model::remove_power_pellet(const std::shared_ptr<entity::PowerPellet> &pp_to_remove) {

    }
}
