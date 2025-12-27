/***************************************************************
 * Project:       Pacman
 * File:          File_Reader.h
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
#ifndef PACMAN_FILE_READER_H
#define PACMAN_FILE_READER_H

#include <memory>
#include <unordered_map>
#include "infra/ast/Game.h"
#include "../ast/view/View.h"
#include "infra/io/Reader.h"

namespace infra::io {
    class File_Reader : public std::enable_shared_from_this<File_Reader>{

        public:
        explicit File_Reader(std::string  conf_directory);
        void add_Reader(const std::string& extension, const std::shared_ptr<Reader> &reader);

        [[nodiscard]] ast::Sprite read_Sprite(const std::string& filename) const;
        [[nodiscard]] ast::SpriteList read_SpriteList(const std::string& filename) const;
        [[nodiscard]] ast::ComplexSprite read_Sprits_Group(const std::string& filename) const;
        [[nodiscard]] ast::View read_View(const std::string &filename) const;
        [[nodiscard]] ast::Model read_Model(const std::string &filename) const;
        [[nodiscard]] ast::ScoreSetup read_ScoreSetup(const std::string &filename) const;
        [[nodiscard]] ast::ScoreBord read_ScoreBord(const std::string &filename) const;
        [[nodiscard]] ast::Game read_Game(const std::string &filename) const;

        void save_ScoreBord(const ast::ScoreBord & info) const;
    protected:
        std::shared_ptr<Reader> get_Reader(const std::string& path) const;
        static std::string get_extension(const std::string& path);
    private:

        std::string conf_directory_;

        std::unordered_map<
            std::string,
            std::shared_ptr<Reader>
        > readers_;
    };
}

#endif //PACMAN_FILE_READER_H
