/***************************************************************
 * Project:       Pacman
 * File:          Reader.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-26
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
#ifndef PACMAN_READER_H
#define PACMAN_READER_H
#include <memory>

#include "infra/ast/view/View.h"
#include "infra/ast/Game.h"
#include "infra/ast/view/sprites/SpriteList.h"

namespace infra::io {

    class File_Reader;

    /**
     * @brief Abstract interface for reading and writing game-related data.
     *
     * Provides methods to read sprites, sprite lists, complex sprites,
     * views, models, score setups, scoreboards, and full game data.
     * Also supports saving a scoreboard.
     */
    class Reader {
        public:
        virtual ~Reader() = default;

        /**
         * @brief Reads a single sprite from a file.
         *
         * @param path Path to the sprite file
         * @return Parsed ast::Sprite
         */
        [[nodiscard]] virtual ast::Sprite read_Sprite(const std::string& path) const = 0;

        /**
         * @brief Reads a list of sprites from a file.
         *
         * @param path Path to the sprite list file
         * @return Parsed ast::SpriteList
         */
        [[nodiscard]] virtual ast::SpriteList read_SpriteList(const std::string& path) const = 0;

        /**
         * @brief Reads a group of complex sprites from a file.
         *
         * @param path Path to the complex sprite group file
         * @return Parsed ast::ComplexSprite
         */
        [[nodiscard]] virtual ast::ComplexSprite read_Sprits_Group(const std::string& path) const = 0;

        /**
         * @brief Reads a view configuration from a file.
         *
         * @param path Path to the view file
         * @param fr Shared pointer to a File_Reader (for file access)
         * @return Parsed ast::View
         */
        [[nodiscard]] virtual ast::View read_View(const std::string& path, const std::shared_ptr<const File_Reader>& fr) const = 0;

        /**
         * @brief Reads a model from a file.
         *
         * @param path Path to the model file
         * @return Parsed ast::Model
         */
        [[nodiscard]] virtual ast::Model read_Model(const std::string& path) const = 0;

        /**
         * @brief Reads score setup data from a file.
         *
         * @param filename Path to the score setup file
         * @return Parsed ast::ScoreSetup
         */
        [[nodiscard]] virtual ast::ScoreSetup read_ScoreSetup(const std::string &filename) const = 0;

        /**
         * @brief Reads a scoreboard from a file.
         *
         * @param filename Path to the scoreboard file
         * @return Parsed ast::ScoreBord
         */
        [[nodiscard]] virtual ast::ScoreBord read_ScoreBord(const std::string &filename, const std::string formal_path) const = 0;

        /**
         * @brief Reads the complete game data from a file.
         *
         * @param path Path to the game file
         * @param fr Shared pointer to a File_Reader
         * @return Parsed ast::Game
         */
        [[nodiscard]] virtual ast::Game read_Game(const std::string& path, const std::shared_ptr<const File_Reader>& fr) const = 0;

        /**
         * @brief Saves a scoreboard to its file.
         *
         * @param info Scoreboard to save
         */
        virtual void save_ScoreBord(const ast::ScoreBord & info, const std::string formal_path) const = 0;
    };
}

#endif //PACMAN_READER_H