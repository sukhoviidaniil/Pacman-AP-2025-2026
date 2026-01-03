/***************************************************************
 * Project:       Pacman
 * File:          Score.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-26
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
#ifndef PACMAN_AST_SCORE_H
#define PACMAN_AST_SCORE_H
#include <cstdint>
#include <string>
#include <vector>

#include "Node.h"


namespace infra::ast {

    struct ScoreSetup : Node {
        // --- Base ---
        unsigned int lives_remaining = 3;
        unsigned int level = 1;
        unsigned int points_score = 0;

        // --- Coins ---
        float time_since_the_last_coin_collection = 0.f;

        unsigned int coin_award_amount = 10;
        unsigned int coin_max_award_level = 10;
        unsigned int coin_award_level = 0;

        float coin_RR_Time_until_reduction  = 5.f;
        float coin_RR_Time_between_reductions = 1.f;

        // --- Ghosts ---
        float time_since_the_last_ghost_collection = 0.f;

        unsigned int ghost_award_amount = 200;
        unsigned int ghost_max_award_level = 4;
        unsigned int ghost_award_level = 0;

        float ghost_RR_Time_until_reset = 6.f;
    };

    struct ScoreInfo : Node {
        std::uint64_t id = 0;
        unsigned int lives_remaining = 3;
        unsigned int level = 1;
        unsigned int points_score = 0;
        ScoreInfo() = default;

        bool operator<(const ScoreInfo& other) const noexcept {
            return points_score < other.points_score;
        }

        bool operator>(const ScoreInfo& other) const noexcept {
            return points_score > other.points_score;
        }
    };

    struct ScoreBord : Node {
        std::string file;
        size_t bord_size;

        // mirrors infra::ScoreBord
        ScoreSetup score_setup;
        std::vector<ScoreInfo> scores;
    };
}

#endif //PACMAN_AST_SCORE_H