/***************************************************************
 * Project:       Pacman
 * File:          Const_Score.h
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
#ifndef PACMAN_CONST_SCORE_H
#define PACMAN_CONST_SCORE_H
#include "ScoreBord.h"

namespace infra {
    class Const_Score {
    public:
        explicit Const_Score(const Score& score) noexcept
            : score_(score) {}

        [[nodiscard]] ast::ScoreInfo get_score_info() const {
            return score_.get_score_info();
        }

        [[nodiscard]] unsigned int lives_remaining() const {
            return score_.lives_remaining();
        }

        [[nodiscard]] unsigned int level() const {
            return score_.level();
        }

        [[nodiscard]] unsigned int points_score() const {
            return score_.points_score();
        }

    private:
        const Score& score_;
    };

    // --------------------------------------

    class Const_ScoreBord {
    public:
        explicit Const_ScoreBord(const ScoreBord& bord) noexcept
            : bord_(bord) {}

        [[nodiscard]] const std::vector<ast::ScoreInfo>& all_scores() const {
            return bord_.all_scores();
        }

        [[nodiscard]] size_t size() const {
            return bord_.all_scores().size();
        }

        [[nodiscard]] std::string file() const {
            return bord_.file();
        }

    private:
        const ScoreBord& bord_;
    };
}

#endif //PACMAN_CONST_SCORE_H