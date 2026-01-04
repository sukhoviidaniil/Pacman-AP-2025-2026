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
    /**
     * @brief Tracks and manages the player's score and progression.
     *
     * Stores lives, level, points, and handles coin and ghost rewards
     * with timing-based reward reduction mechanics.
     */
    class Score {
    public:
        explicit Score();
        explicit Score(std::uint64_t id, const ast::ScoreSetup& score_info);


        /**
         * @brief Get the unique ID of this score instance.
         */
        [[nodiscard]] std::uint64_t id() const;

        /**
         * @brief Returns the current score information as a ScoreInfo object.
         */
        [[nodiscard]] ast::ScoreInfo get_score_info() const;
        [[nodiscard]] unsigned int lives_remaining() const;
        [[nodiscard]] unsigned int level() const;
        [[nodiscard]] unsigned int points_score() const;

        // --- Coins ---
        [[nodiscard]] unsigned int coin_collection();

        void all_coins_collected();

        // --- Ghosts ---
        [[nodiscard]] unsigned int ghost_collection();

        /**
         * @brief Decrement lives when Pacman dies.
         */
        void pakman_died();

        /**
         * @brief Updates timers and reward reductions over time.
         *
         * @param delta Time elapsed since last update
         */
        void run(float delta);
    private:
        std::uint64_t id_; ///< Unique identifier

        unsigned int lives_remaining_ = 3; ///< Current number of lives
        unsigned int level_ = 1; ///< Current level
        unsigned int points_score_ = 0; ///< Total points

        // --- Coin reward management ---
        float time_since_the_last_coin_collection_ = 0.f; ///< Timer for coin collection
        unsigned int coin_award_amount_ = 10; ///< Points per coin at current reward level
        unsigned int coin_max_award_level_ = 10; ///< Maximum coin reward level
        unsigned int coin_award_level_ = 0; ///< Current coin reward level
        float coin_RR_Time_until_reduction_  = 5.f; ///< Time until reward reduction begins
        float coin_RR_Time_between_reductions_ = 1.f; ///< Interval between reward reductions

        // --- Ghost reward management ---
        float time_since_the_last_ghost_collection_ = 0.f; ///< Timer for ghost collection
        unsigned int ghost_award_amount_ = 200; ///< Points per ghost
        unsigned int ghost_max_award_level_ = 4; ///< Maximum ghost reward multiplier
        unsigned int ghost_award_level_ = 0; ///< Current ghost reward level
        float ghost_RR_time_until_reset_ = 6.f; ///< Time until ghost reward resets
    };
}

#endif //PACMAN_SCORE_H
