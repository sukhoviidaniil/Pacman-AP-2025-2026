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

    File_Reader::File_Reader(const std::string &texture_folder, const std::string& configuration_folder):
    texture_folder_(texture_folder), configuration_folder_(configuration_folder){
    }

    void File_Reader::add_Reader(const std::string &extension, const std::shared_ptr<Reader> &reader) {
        readers_[extension] = reader;
    }

    sf::Texture& File_Reader::load_SFML_texture(Graphics::SFML_Manager& manager, const std::string& name) const {
        if (auto texOpt = manager.get_Texture(name); texOpt) {
            return texOpt->get();
        }

        sf::Texture texture;
        texture.loadFromFile(texture_folder_ + name);
        manager.add_Texture(name, texture);

        return manager.get_Texture(name)->get();
    }

    void File_Reader::load_SFML_Sprite(Graphics::SFML_Manager &manager, const std::string &filename) const {
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        reader->load_SFML_Sprite(manager, configuration_folder_ + filename);
    }

    void File_Reader::load_SFML_Sprite_Group(Graphics::SFML_Manager &manager, const std::string &filename) const {
        const std::string extension = get_extension(filename);
        const std::shared_ptr<Reader> reader = get_reader(extension);
        if (!reader) {
            throw std::runtime_error("No suitable reader was found for the configuration type " + extension);
        }
        reader->load_SFML_Sprite_Group(manager, configuration_folder_ + filename);
    }

    Stage_Manager File_Reader::make_Stage_Manager(const Graphics::SFML_Manager &manage, const std::string &path) {
    }
}
