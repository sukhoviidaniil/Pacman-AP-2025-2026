/***************************************************************
 * Project:       Pacman
 * File:          ScoreBord.cpp
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

#include "infra/internal/ScoreBord.h"

#include <algorithm>

namespace infra {

    ScoreBord::ScoreBord(const std::string &file, size_t bord_size, const std::vector<ast::ScoreInfo> &all_scores)  : file_(file), bord_size_(bord_size), all_scores_(all_scores) {
    }

    ScoreBord::ScoreBord(const ast::ScoreBord &score) : file_(score.file), bord_size_(score.bord_size), all_scores_(score.scores) {
    }

    void ScoreBord::sort_and_trim() {
        std::sort(all_scores_.begin(), all_scores_.end(), std::greater<ast::ScoreInfo>{});
        if (all_scores_.size() > bord_size_) {
            all_scores_.resize(bord_size_);
        }
    }

    void ScoreBord::add_to_bord(const Score &score) {
        all_scores_.push_back(score.get_score_info());
        sort_and_trim();
    }


    const std::vector<ast::ScoreInfo> & ScoreBord::all_scores() const {
        return all_scores_;
    }

    std::string ScoreBord::file() const{
        return file_;
    }
}
