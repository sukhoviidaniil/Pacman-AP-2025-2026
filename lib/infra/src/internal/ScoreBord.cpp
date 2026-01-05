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

    ScoreBord::ScoreBord(const std::string &file, size_t bord_size, const std::vector<ast::ScoreInfo> &all_scores)
    : file_(file), bord_size_(bord_size), all_scores_(all_scores) {
        sync_next_id();
        sort_and_trim();
    }

    ScoreBord::ScoreBord(const ast::ScoreBord &score) : file_(score.file), bord_size_(score.bord_size), all_scores_(score.scores) {
        sync_next_id();
        sort_and_trim();
    }

    ast::ScoreBord ScoreBord::save() const {
        ast::ScoreBord result{};
        result.file = file_;
        result.bord_size = bord_size_;
        result.score_setup = score_setup_;
        result.scores = all_scores_;
        return result;
    }

    void ScoreBord::sort_and_trim() {
        std::sort(all_scores_.begin(), all_scores_.end(), std::greater<ast::ScoreInfo>{});
        if (all_scores_.size() > bord_size_) {
            all_scores_.resize(bord_size_);
        }
    }

    void ScoreBord::add_to_bord(const ast::ScoreInfo info) {

        // already exists → ignore
        auto it = std::find_if(
            all_scores_.begin(),
            all_scores_.end(),
            [&](const ast::ScoreInfo& s) { return s.id == info.id; }
        );

        if (it != all_scores_.end())
            return;

        all_scores_.push_back(info);
        sort_and_trim();
    }


    void ScoreBord::add_to_bord(const Score &score) {
        const auto info = score.get_score_info();
        add_to_bord(info);
    }

    const std::vector<ast::ScoreInfo> & ScoreBord::all_scores() const {
        return all_scores_;
    }

    std::string ScoreBord::file() const{
        return file_;
    }

    std::unique_ptr<Score> ScoreBord::create_score()  {
        return std::make_unique<Score>(next_id_++, score_setup_);
    }
    void ScoreBord::sync_next_id()  {
        for (const auto& s : all_scores_)
            next_id_ = std::max(next_id_, s.id + 1);
    }
}
