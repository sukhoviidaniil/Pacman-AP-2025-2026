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

    Score::Score(const ast::ScoreSetup &score_info) :
    lives_remaining_(score_info.lives_remaining),
    level_(score_info.level),
    points_score_(score_info.points_score),
    time_since_the_last_coin_collection_(score_info.time_since_the_last_coin_collection),
    award_amount_(score_info.award_amount),
    max_award_level_(score_info.max_award_level),
    RR_Time_until_reduction_(score_info.RR_Time_until_reduction),
    RR_Time_between_reductions_(score_info.RR_Time_between_reductions)
    {
    }

    ast::ScoreInfo Score::get_score_info() const {
        ast::ScoreInfo s;
        s.lives_remaining = lives_remaining_;
        s.level = level_;
        s.points_score = points_score_;
        return s;
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
        award_level_ = (award_level_ + 1) % max_award_level_;
        const unsigned int added = award_amount_ * award_level_;
        points_score_ += added;
        return added;
    }

    void Score::pakman_died() {
        if (lives_remaining_ > 0) {
            --lives_remaining_;
        }
        award_level_ = 0;
        time_since_the_last_coin_collection_ = 0.f;
    }

    void Score::run(float delta) {

        time_since_the_last_coin_collection_ += delta;

        if (award_level_ == 0) {
            return;
        }

        if (time_since_the_last_coin_collection_ < RR_Time_until_reduction_) {
            return;
        }

        const float elapsed = time_since_the_last_coin_collection_ - RR_Time_until_reduction_;

        const unsigned int reductions = static_cast<unsigned int>(elapsed / RR_Time_between_reductions_);

        if (reductions > 0) {
            if (reductions >= award_level_) {
                award_level_ = 0;
            } else {
                award_level_ -= reductions;
            }
            time_since_the_last_coin_collection_ = RR_Time_until_reduction_ + std::fmod(elapsed, RR_Time_between_reductions_);
        }
    }
}
