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

#include "core/File_Reader.h"

namespace Core {
    std::string File_Reader::get_extension(const std::string &path) {
        const auto pos = path.find_last_of('.');
        if (pos == std::string::npos) return ""; // no extensions
        return path.substr(pos); // including the dot: “.json”
    }

    std::shared_ptr<Reader> File_Reader::get_reader(const std::string &filetype) const {
        const auto it = readers_.find(filetype);
        if (it == readers_.end()) return nullptr;
        return it->second;
    }

    File_Reader::File_Reader(std::string  graphics_folder, std::string  configuration_folder):
    graphics_folder_(std::move(graphics_folder)), configuration_folder_(std::move(configuration_folder)){
    }

    void File_Reader::add_Reader(const std::string &extension, const std::shared_ptr<Reader> &reader) {
        readers_[extension] = reader;
    }

    void File_Reader::add_SFML_Manager(const std::shared_ptr<Graphics::SFML_Manager> &sfml_manager) {
        sfml_manager_ = sfml_manager;
    }

    std::shared_ptr<Graphics::SFML_Manager> File_Reader::get_SFML_Manager() const {
        return sfml_manager_;
    }

    const sf::Texture & File_Reader::load_SFML_texture(const std::string &filename) const {

        if (sfml_manager_ == nullptr) {
            throw std::runtime_error("No sfml manager found.");
        }
        if (const auto texOpt = sfml_manager_->get_Texture(filename); texOpt) {
            return texOpt->get();
        }
        sf::Texture texture;
        texture.loadFromFile(graphics_folder_ + filename);
        sfml_manager_->add_Texture(filename, texture);
        return sfml_manager_->get_Texture(filename)->get();
    }

    const sf::Texture& File_Reader::load_SFML_texture(
        const std::shared_ptr<Graphics::SFML_Manager>& manager, const std::string& filename
        ) const {

        if (const auto texOpt = manager->get_Texture(filename); texOpt) {
            return texOpt->get();
        }
        sf::Texture texture;
        texture.loadFromFile(graphics_folder_ + filename);
        manager->add_Texture(filename, std::move(texture));
        return manager->get_Texture(filename)->get();
    }

    void File_Reader::load_SFML_Sprite(const std::string &filename) const {

        if (sfml_manager_ == nullptr) {
            throw std::runtime_error("No sfml manager found.");
        }
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        reader->load_SFML_Sprite(sfml_manager_, configuration_folder_ + filename);
    }

    void File_Reader::load_SFML_Sprite(
        const std::shared_ptr<Graphics::SFML_Manager>& manager, const std::string& filename
        ) const {
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        reader->load_SFML_Sprite(manager, configuration_folder_ + filename);
    }

    void File_Reader::load_SFML_Sprite_Group(
        const std::string &filename) const {

    }

    void File_Reader::load_SFML_Sprite_Group(
        const std::shared_ptr<Graphics::SFML_Manager>& manager, const std::string &filename
        ) const {
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        reader->load_SFML_Sprite_Group(manager, configuration_folder_ + filename);
    }

    void File_Reader::load_SFML_Manager(const std::string &filename) {
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }

        std::string path = configuration_folder_ + filename;
        std::shared_ptr<const File_Reader> self = shared_from_this();
        sfml_manager_ = reader->load_SFML_Manager(self, filename);
    }

    std::shared_ptr<Logic::Collision::HitBoxe> File_Reader::make_HitBoxe(const std::string &filename) const {
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        // TODO
    }

    std::shared_ptr<Stage> File_Reader::load_Stage(const std::string &filename) const {
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        // TODO
    }

    Stage_Manager File_Reader::load_Stage_Manager(const std::string &filename) {
        auto self = shared_from_this(); // shared_ptr<File_Reader>
        std::shared_ptr<const File_Reader> c_self = self;
        Stage_Manager sm = Stage_Manager(c_self);

        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        std::string path = configuration_folder_ + filename;
        return reader->load_Stage_Manager(self, path);
    }

    Info::Game_Info File_Reader::get_Game_Info(const std::string &filename) const {
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        return reader->get_Game_Info(configuration_folder_ + filename);
    }
}
