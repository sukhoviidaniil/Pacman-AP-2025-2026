/***************************************************************
 * Project:       Pacman
 * File:          Sprite_Group.h
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
#ifndef PACMAN_SPRITE_GROUP_H
#define PACMAN_SPRITE_GROUP_H


#include "math/Vector2.h"
#include "SFML/Graphics.hpp"

#include "func/json.hpp"
#include <vector>


namespace Graphics {
    // Used for Entities like Ghosts
    // Hold FULL info about render of this ONE Entity
    class Sprite_Group {
        std::vector<
            // key - status of Sprite;
            std::unordered_map<
                // key - direction of Sprite;
                Math::Vector2,
                // animation
                std::vector<sf::Sprite>,
                // custom hash function
                Math::Vector2Hash
            >
        > entity_sprites_;
        unsigned int animation_index = 0;
        public:
        Sprite_Group();

        explicit Sprite_Group(const std::vector<std::unordered_map<Math::Vector2,std::vector<sf::Sprite>,Math::Vector2Hash>> &data);

        void render(sf::RenderWindow& window);
    };
}

#endif //PACMAN_SPRITE_GROUP_H