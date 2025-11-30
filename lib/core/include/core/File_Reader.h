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

#include "core/readers/Reader.h"
#include "graphics//SFML_Manager.h"
#include "core/Stage_Manager.h"

#include <memory>
#include <unordered_map>

namespace Core {
    class File_Reader {

        std::string texture_folder_;
        std::string configuration_folder_;

        std::unordered_map<
            std::string,
            std::shared_ptr<Reader>
        > readers_;

        protected:

        static std::string get_extension(const std::string& path);

        std::shared_ptr<Reader> get_reader(const std::string &filetype) const;

        public:
        File_Reader(const std::string &texture_folder, const std::string &configuration_folder);

        void add_Reader(const std::string& extension, const std::shared_ptr<Reader> &reader);

        sf::Texture& load_SFML_texture(Graphics::SFML_Manager& manager, const std::string& name) const;
        void load_SFML_Sprite(Graphics::SFML_Manager& manager, const std::string& filename) const;
        void load_SFML_Sprite_Group(Graphics::SFML_Manager& manager, const std::string& filename) const;

        Stage_Manager make_Stage_Manager(const Graphics::SFML_Manager& manage, const std::string& path);
    };
}

#endif //PACMAN_FILE_READER_H
