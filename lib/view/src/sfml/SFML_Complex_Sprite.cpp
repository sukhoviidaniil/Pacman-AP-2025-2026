/***************************************************************
 * Project:       Pacman
 * File:          SFML_Complex_Sprite.cpp
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

#include "view/sfml/SFML_Complex_Sprite.h"

namespace view {
    SFML_Complex_Sprite::SFML_Complex_Sprite(
        const std::vector<std::unordered_map<infra::math::Vector2, std::vector<sf::Sprite>, infra::math::Vector2Hash>> &data) : sprites_(data)
    {
    }
}
