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

#include "info/Game_Info.h"

namespace Core {
    class File_Reader : public std::enable_shared_from_this<File_Reader>{

        std::string graphics_folder_;
        std::string configuration_folder_;

        std::shared_ptr<Graphics::SFML_Manager> sfml_manager_;

        std::unordered_map<
            std::string,
            std::shared_ptr<Reader>
        > readers_;

        protected:

        static std::string get_extension(const std::string& path);

        std::shared_ptr<Reader> get_reader(const std::string &filetype) const;

        public:
        File_Reader(std::string graphics_folder, std::string configuration_folder);
        void add_Reader(const std::string& extension, const std::shared_ptr<Reader> &reader);
        void add_SFML_Manager(const std::shared_ptr<Graphics::SFML_Manager>& sfml_manager);
        std::shared_ptr<Graphics::SFML_Manager> get_SFML_Manager() const;

        const sf::Texture& load_SFML_texture(const std::string& name) const;
        const sf::Texture& load_SFML_texture(const std::shared_ptr<Graphics::SFML_Manager>& manager, const std::string& name) const;
        void load_SFML_Sprite(const std::string& filename) const;
        void load_SFML_Sprite(const std::shared_ptr<Graphics::SFML_Manager>& manager, const std::string& filename) const;
        void load_SFML_Sprite_Group(const std::string& filename) const;
        void load_SFML_Sprite_Group(const std::shared_ptr<Graphics::SFML_Manager>& manager, const std::string& filename) const;
        void load_SFML_Manager(const std::string &filename);

        std::shared_ptr<Logic::Collision::HitBoxe> make_HitBoxe(const std::string& filename) const;

        std::shared_ptr<Stage> load_Stage(const std::string& filename) const;
        Stage_Manager load_Stage_Manager(const std::string& filename);

        Info::Game_Info get_Game_Info(const std::string& filename) const;
    };
}

#endif //PACMAN_FILE_READER_H
