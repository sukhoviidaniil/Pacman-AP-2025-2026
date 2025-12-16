/***************************************************************
 * Project:       Pacman
 * File:          SFML_Render.cpp
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

/*
#include "graphics/SFML_Manager.h"

namespace graphics {
    SFML_Manager::SFML_Manager() = default;

    SFML_Manager::~SFML_Manager() = default;

    void SFML_Manager::add_Texture(const std::string &name, const sf::Texture& texture) {
        textures_[name] = texture;
    }

    std::optional<std::reference_wrapper<const sf::Texture>> SFML_Manager::get_Texture(const std::string &name) const {
        const auto it = textures_.find(name);
        if (it == textures_.end()) return std::nullopt;
        return it->second;
    }

    void SFML_Manager::add_Sprite(const std::string &name, const std::shared_ptr<sf::Sprite> &sprite) {
        sprites_[name] = sprite;
    }

    std::shared_ptr<sf::Sprite> SFML_Manager::get_Sprite(const std::string &name) const {
        const auto it = sprites_.find(name);
        if (it == sprites_.end()) return nullptr;
        return it->second;
    }

    void SFML_Manager::add_Sprite_Group(const std::string &name, const std::shared_ptr<Sprite_Group> &sprite_group) {
        sprite_groups_[name] = sprite_group;
    }

    std::shared_ptr<Sprite_Group> SFML_Manager::get_Sprite_Group(const std::string &name) const{
        const auto it = sprite_groups_.find(name);
        if (it == sprite_groups_.end()) return nullptr;
        return it->second;
    }
}
*/