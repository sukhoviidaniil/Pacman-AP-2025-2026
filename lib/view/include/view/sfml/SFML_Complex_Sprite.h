/***************************************************************
 * Project:       Pacman
 * File:          SFML_Complex_Sprite.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-17
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
#ifndef PACMAN_SFML_COMPLEX_SPRITE_H
#define PACMAN_SFML_COMPLEX_SPRITE_H
#include <unordered_map>
#include <vector>

#include "infra/math/Vector2.h"
#include "SFML/Graphics/Sprite.hpp"

namespace view {
    class SFML_Complex_Sprite {
        // key - status of Sprite;
        std::vector<
            // key - direction of Sprite;
            std::unordered_map<
                infra::math::Vector2,
                // animation
                std::vector<
                    sf::Sprite
                >,
                // custom hash function
                infra::math::Vector2Hash
            >
        > sprites_;
    public:
        explicit SFML_Complex_Sprite(const std::vector<std::unordered_map<infra::math::Vector2,std::vector<sf::Sprite>, infra::math::Vector2Hash>>& data);
    };
}

#endif //PACMAN_SFML_COMPLEX_SPRITE_H