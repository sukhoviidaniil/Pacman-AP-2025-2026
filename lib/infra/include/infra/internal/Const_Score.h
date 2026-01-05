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
    /**
     * @brief Read-only wrapper around a Score instance.
     *
     * Provides const access to score information without allowing modification.
     */
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

        [[nodiscard]] ast::ScoreInfo score_info() const {
            return score_.get_score_info();
        }

    private:
        const Score& score_; ///< Reference to the underlying Score
    };

    // --------------------------------------

    /**
     * @brief Read-only wrapper around a ScoreBord instance.
     *
     * Provides const access to the stored scores and scoreboard metadata.
     */
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
        const ScoreBord& bord_; ///< Reference to the underlying ScoreBord
    };
}

#endif //PACMAN_CONST_SCORE_H