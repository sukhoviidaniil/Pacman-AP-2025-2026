/***************************************************************
 * Project:       Pacman
 * File:          Score.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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
#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H

#include "infra/ast/Score.h"

namespace infra {
    class Score {
    public:
        explicit Score();
        explicit Score(std::uint64_t id, const ast::ScoreSetup& score_info);
        [[nodiscard]] std::uint64_t id() const;
        [[nodiscard]] ast::ScoreInfo get_score_info() const;
        [[nodiscard]] unsigned int lives_remaining() const;
        [[nodiscard]] unsigned int level() const;
        [[nodiscard]] unsigned int points_score() const;

        // --- Coins ---
        [[nodiscard]] unsigned int coin_collection();

        // --- Ghosts ---
        [[nodiscard]] unsigned int ghost_collection();

        void pakman_died();
        void run(float delta);
    private:
        std::uint64_t id_;

        unsigned int lives_remaining_ = 3;
        unsigned int level_ = 1;
        unsigned int points_score_ = 0;

        float time_since_the_last_coin_collection_ = 0;

        // Reward
        unsigned int coin_award_amount_ = 10; /// How many points will be added for each reward level
        unsigned int coin_max_award_level_ = 10; /// Maximum reward level (when picking up a coin, it is set to this value)
        unsigned int coin_award_level_ = 0; /// Current reward level (this value will decrease over time)

        // (RR - reward reduction)
        float coin_RR_Time_until_reduction_  = 5; /// Time until reduction for coin collection rewards
        float coin_RR_Time_between_reductions_ = 1; /// Time until reduction for coin collection rewards

        // --- Ghosts reward ---
        float time_since_the_last_ghost_collection_ = 0.f;

        unsigned int ghost_award_amount_ = 200;
        unsigned int ghost_max_award_level_ = 4;   // 200, 400, 800, 1600
        unsigned int ghost_award_level_ = 0;

        float ghost_RR_time_until_reset_ = 6.f;
    };
}

#endif //PACMAN_SCORE_H
