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
#include <string>
#include <vector>

#include "Node.h"


namespace infra::ast {

    struct ScoreSetup : Node {
        unsigned int lives_remaining = 3;
        unsigned int level = 1;
        unsigned int points_score = 0;

        float time_since_the_last_coin_collection = 0;

        // Reward
        unsigned int award_amount = 10; /// How many points will be added for each reward level
        unsigned int max_award_level = 10; /// Maximum reward level (when picking up a coin, it is set to this value)
        unsigned int award_level = 0; /// Current reward level (this value will decrease over time)

        // (RR - reward reduction)
        float RR_Time_until_reduction  = 5; /// Time until reduction for coin collection rewards
        float RR_Time_between_reductions = 1; /// Time until reduction for coin collection rewards
    };

    struct ScoreInfo : Node {
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
        std::vector<ScoreInfo> scores;
    };
}

#endif //PACMAN_AST_SCORE_H