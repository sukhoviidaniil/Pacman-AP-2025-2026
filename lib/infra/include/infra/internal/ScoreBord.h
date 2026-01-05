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
    /**
     * @brief Manages a scoreboard with multiple player scores.
     *
     * Provides functionality to sort, trim, and add new scores,
     * and to create Score instances with unique IDs.
     */
    class ScoreBord {
    public:
        /**
         * @brief Constructs a scoreboard from a file path and initial scores.
         *
         * @param file Path to store/load the scoreboard
         * @param bord_size Maximum number of scores to keep
         * @param all_scores Initial list of scores
         */
        explicit ScoreBord(const std::string& file, size_t bord_size, const std::vector<ast::ScoreInfo> &all_scores);

        /**
         * @brief Constructs a scoreboard from an existing AST ScoreBord node.
         */
        explicit ScoreBord(const ast::ScoreBord &score);

        [[nodiscard]] ast::ScoreBord save() const;

        /**
         * @brief Sorts the scores in descending order and trims to the maximum size.
         */
        void sort_and_trim();

        void add_to_bord(ast::ScoreInfo info);

        /**
         * @brief Adds a new score to the scoreboard.
         *
         * @param score Score instance to add
         */
        void add_to_bord(const Score& score);

        /**
         * @brief Returns all stored scores.
         */
        [[nodiscard]] const std::vector<ast::ScoreInfo> & all_scores() const;

        /**
         * @brief Returns the file path associated with the scoreboard.
         */
        [[nodiscard]] std::string file() const;

        /**
         * @brief Creates a new Score instance with a unique ID.
         */
        std::unique_ptr<Score> create_score();
    private:
        /**
         * @brief Synchronizes the next available unique ID.
         */
        void sync_next_id();
        std::uint64_t next_id_ = 1; ///< Next unique ID for scores
        std::string file_; ///< File path for saving/loading
        ast::ScoreSetup score_setup_; ///< Score setup configuration
        size_t bord_size_ = 5; ///< Maximum number of scores
        std::vector<ast::ScoreInfo> all_scores_; ///< Stored scores
    };
}

#endif //PACMAN_SCOREBORD_H