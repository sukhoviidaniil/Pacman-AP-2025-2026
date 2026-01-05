/***************************************************************
 * Project:       Pacman
 * File:          File_Reader.cpp
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

#include <utility>

#include "infra/io/File_Reader.h"

#include "infra/ast/model/Model.h"

namespace infra::io {

    File_Reader::File_Reader(std::string conf_directory) : conf_directory_(std::move(conf_directory)) {
    }

    void File_Reader::add_Reader(const std::string &extension, const std::shared_ptr<Reader> &reader) {
        const auto it = readers_.find(extension);
        if (it != readers_.end()) {
            throw std::runtime_error("There is already a reader for type " + extension);
        }
        readers_[extension] = reader;
    }

    ast::Sprite File_Reader::read_Sprite(const std::string &filename) const {
        const std::shared_ptr<Reader> reader = get_Reader(filename);
        return reader->read_Sprite(conf_directory_ + filename);
    }

    ast::SpriteList File_Reader::read_SpriteList(const std::string &filename) const {
        const std::shared_ptr<Reader> reader = get_Reader(filename);
        return reader->read_SpriteList(conf_directory_ + filename);
    }

    ast::ComplexSprite File_Reader::read_Sprits_Group(const std::string &filename) const {
        const std::shared_ptr<Reader> reader = get_Reader(filename);
        return reader->read_Sprits_Group(conf_directory_ + filename);
    }

    ast::View File_Reader::read_View(const std::string &filename) const {
        const std::shared_ptr<Reader> reader = get_Reader(filename);
        return reader->read_View(conf_directory_ + filename, shared_from_this());
    }

    ast::Model File_Reader::read_Model(const std::string &filename) const {
        const std::shared_ptr<Reader> reader = get_Reader(filename);
        return reader->read_Model(conf_directory_ + filename);
    }

    ast::ScoreSetup File_Reader::read_ScoreSetup(const std::string &filename) const {
        const std::shared_ptr<Reader> reader = get_Reader(filename);
        return reader->read_ScoreSetup(conf_directory_ + filename);
    }

    ast::ScoreBord File_Reader::read_ScoreBord(const std::string &filename) const {
        const std::shared_ptr<Reader> reader = get_Reader(filename);
        return reader->read_ScoreBord(conf_directory_ + filename, filename);
    }

    ast::Game File_Reader::read_Game(const std::string &filename) const {
        const std::shared_ptr<Reader> reader = get_Reader(filename);
        return reader->read_Game(conf_directory_ + filename, shared_from_this());
    }

    void File_Reader::save_ScoreBord(const ast::ScoreBord &info) const {
        const std::shared_ptr<Reader> reader = get_Reader(info.file);
        reader->save_ScoreBord(info, conf_directory_ + info.file);
    }

    std::shared_ptr<Reader> File_Reader::get_Reader(const std::string &path) const {
        const std::string extension = get_extension(path);
        const auto it = readers_.find(extension);
        if (it == readers_.end()) {
            throw std::runtime_error("No suitable reader was found for the type " + extension);
        }
        return it->second;
    }

    std::string File_Reader::get_extension(const std::string &path) {
        const auto pos = path.find_last_of('.');
        if (pos == std::string::npos) return ""; // no extensions
        return path.substr(pos); // including the dot: “.json”
    }
}
