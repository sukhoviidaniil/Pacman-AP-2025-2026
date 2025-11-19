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


#include "graphics/Sprite_Group.h"

#include "../../include/graphics/info/Expression_Info.h"
#include "func/func_get_sprite_from_json.h"

namespace Graphics {
    Sprite_Group::Sprite_Group() = default;

    Sprite_Group::Sprite_Group( const std::vector<std::unordered_map<Math::Vector2, std::vector<sf::Sprite>, Math::Vector2Hash>> &data) : entity_sprites_(data) {

    }

    void Sprite_Group::render(sf::RenderWindow &window) {
        /*
        const unsigned int status = info.status;
        const Math::Vector2 dir = info.direction;
        const Math::Vector2 pos = info.position;

        std::vector<sf::Sprite>* animation = nullptr;

        if (status < entity_sprites_.size()) {
            auto& map = entity_sprites_[status];
            auto it = map.find(dir);
            if (it != map.end()) {
                animation = &it->second;
            }else {
                it = map.find({0,0});
                if (it != map.end()) {
                    animation = &it->second;
                }
            }
        }
        if (animation) {
            if (animation_index >= animation->size()) {
                animation_index = 0;
            }
            sf::Sprite& sprite = (*animation)[animation_index];
            sprite.setPosition({pos.x, pos.y});
            window.draw(sprite);
            animation_index++;
        }else {
            throw std::invalid_argument("No animation found for " + info.name);
        }
        */
    }
}
