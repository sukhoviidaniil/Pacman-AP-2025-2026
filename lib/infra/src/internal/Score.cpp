/***************************************************************
 * Project:       Pacman
 * File:          Score.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-21
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

#include "infra/internal/Score.h"

#include <cmath>

namespace infra {
    Score::Score() = default;

    Score::Score(const std::uint64_t id, const ast::ScoreSetup& s)
        : id_(id),
        lives_remaining_(s.lives_remaining),
        level_(s.level),
        points_score_(s.points_score),
        time_since_the_last_coin_collection_(s.time_since_the_last_coin_collection),
        coin_award_amount_(s.coin_award_amount),
        coin_max_award_level_(s.coin_max_award_level),
        coin_award_level_(s.coin_award_level),
        coin_RR_Time_until_reduction_(s.coin_RR_Time_until_reduction),
        coin_RR_Time_between_reductions_(s.coin_RR_Time_between_reductions),

        time_since_the_last_ghost_collection_(s.time_since_the_last_ghost_collection),
        ghost_award_amount_(s.ghost_award_amount),
        ghost_max_award_level_(s.ghost_max_award_level),
        ghost_award_level_(s.ghost_award_level),
        ghost_RR_time_until_reset_(s.ghost_RR_Time_until_reset)
    {}

    std::uint64_t Score::id() const {
        return id_;
    }

    ast::ScoreInfo Score::get_score_info() const {
        ast::ScoreInfo info;
        info.id = id_;
        info.lives_remaining = lives_remaining_;
        info.level = level_;
        info.points_score = points_score_;
        return info;
    }

    unsigned int Score::lives_remaining() const {
        return lives_remaining_;
    }

    unsigned int Score::level() const {
        return level_;
    }

    unsigned int Score::points_score() const {
        return points_score_;
    }

    unsigned int Score::coin_collection() {
        time_since_the_last_coin_collection_ = 0.f;
        coin_award_level_ = (coin_award_level_ + 1) % coin_max_award_level_;
        const unsigned int added = coin_award_amount_ * coin_award_level_;
        points_score_ += added;
        return added;
    }

    void Score::all_coins_collected() {
        level_++;
    }

    unsigned int Score::ghost_collection() {
        time_since_the_last_ghost_collection_ = 0.f;

        if (ghost_award_level_ < ghost_max_award_level_)
            ++ghost_award_level_;

        const unsigned int reward =
            ghost_award_amount_ * (1u << (ghost_award_level_ - 1));

        points_score_ += reward;
        return reward;
    }

    void Score::pakman_died() {
        if (lives_remaining_ > 0) {
            --lives_remaining_;
        }
        coin_award_level_ = 0;
        time_since_the_last_coin_collection_ = 0.f;
    }

    void Score::run(float delta) {

        time_since_the_last_coin_collection_ += delta;

        if (coin_award_level_ == 0) {
            return;
        }

        if (time_since_the_last_coin_collection_ < coin_RR_Time_until_reduction_) {
            return;
        }

        const float elapsed = time_since_the_last_coin_collection_ - coin_RR_Time_until_reduction_;

        const unsigned int reductions = static_cast<unsigned int>(elapsed / coin_RR_Time_between_reductions_);

        if (reductions > 0) {
            if (reductions >= coin_award_level_) {
                coin_award_level_ = 0;
            } else {
                coin_award_level_ -= reductions;
            }
            time_since_the_last_coin_collection_ = coin_RR_Time_until_reduction_ + std::fmod(elapsed, coin_RR_Time_between_reductions_);
        }

        time_since_the_last_ghost_collection_ += delta;
        if (time_since_the_last_ghost_collection_ >= ghost_RR_time_until_reset_) {
            ghost_award_level_ = 0;
        }
    }
}
