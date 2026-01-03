/***************************************************************
 * Project:       Pacman
 * File:          ScoreBord.h
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
#ifndef PACMAN_SCOREBORD_H
#define PACMAN_SCOREBORD_H


#include <memory>
#include <vector>
#include "Score.h"

namespace infra {
    class ScoreBord {
    public:
        explicit ScoreBord(const std::string& file, size_t bord_size, const std::vector<ast::ScoreInfo> &all_scores);
        explicit ScoreBord(const ast::ScoreBord &score);
        void sort_and_trim();
        void add_to_bord(const Score& score);
        const std::vector<ast::ScoreInfo> & all_scores() const;
        std::string file() const;

        std::unique_ptr<Score> create_score();

    private:
        void sync_next_id();
        std::uint64_t next_id_ = 1;
        std::string file_;
        ast::ScoreSetup score_setup_;
        size_t bord_size_ = 5;
        std::vector<ast::ScoreInfo> all_scores_;
    };
}

#endif //PACMAN_SCOREBORD_H