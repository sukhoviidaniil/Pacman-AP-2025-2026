/***************************************************************
 * Project:       Pacman
 * File:          SFML_Manager.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-09
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
#ifndef PACMAN_SFML_MANAGER_H
#define PACMAN_SFML_MANAGER_H

#include "graphics/Sprite_Group.h"
#include <memory>
namespace Graphics{
    class SFML_Manager{
        // key - name of file
        std::map<
            std::string,
            sf::Texture
        > textures_;

        // key - construct name
        std::map<
            std::string,
            std::shared_ptr<sf::Sprite>
        > sprites_;

        // key - entity name
        std::map<
            std::string,
            std::shared_ptr<Sprite_Group>
        > sprite_groups_;
        public:

        SFML_Manager();
        ~SFML_Manager();

        // ===== Textures =====
        void add_Texture(const std::string& name, const sf::Texture& texture);
        [[nodiscard]] std::optional<std::reference_wrapper<const sf::Texture>> get_Texture(const std::string& name) const;

        // ===== Sprites =====
        void add_Sprite(const std::string& name, const std::shared_ptr<sf::Sprite> &sprite);
        [[nodiscard]] std::shared_ptr<sf::Sprite> get_Sprite(const std::string& name) const;
        void add_Sprite_Group(const std::string& name, const std::shared_ptr<Sprite_Group> &sprite_group);
        [[nodiscard]] std::shared_ptr<Sprite_Group> get_Sprite_Group(const std::string& name) const;
    };
}

#endif