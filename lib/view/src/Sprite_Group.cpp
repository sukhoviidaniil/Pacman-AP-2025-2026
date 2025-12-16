/***************************************************************
 * Project:       Pacman
 * File:          Sprite_Group.cpp
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
#include "graphics/Sprite_Group.h"

namespace graphics {

    Sprite_Group::Sprite_Group() = default;

    Sprite_Group::Sprite_Group( const std::vector<std::unordered_map<math::Vector2, std::vector<sf::Sprite>, math::Vector2Hash>> &data) : entity_sprites_(data) {

    }

    void Sprite_Group::render(
        sf::RenderWindow& window,
        const math::Vector2 &pos,
        const math::Vector2 &dir,
        unsigned int status) {

        if (status>= entity_sprites_.size()) {
            throw std::invalid_argument("No animation found for " + name_ + "; To high status!!!");
        }

        std::vector<sf::Sprite>* animation = nullptr;

        auto& map = entity_sprites_[status];
        auto it = map.find(dir);
        if (it != map.end()) {
            animation = &it->second;
        }else {
            it = map.find({0,0});
            if (it == map.end()) {
                throw std::invalid_argument("No animation found for " + name_);
            }
            animation = &it->second;
        }

        if (!animation) {
            throw std::invalid_argument("No animation found for " + name_);
        }


        if (animation_index >= animation->size()) {
            animation_index = 0;
        }

        sf::Sprite sprite = (*animation)[animation_index];
        sprite.setPosition({pos.x, pos.y});
        window.draw(sprite);
        animation_index++;
    }
}

*/