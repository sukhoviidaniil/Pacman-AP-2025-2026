/***************************************************************
 * Project:       Pacman
 * File:          func_get_sprite_from_json.h
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
#ifndef PACMAN_FUNC_GET_SPRITE_FROM_JSON_H
#define PACMAN_FUNC_GET_SPRITE_FROM_JSON_H
#include "json.hpp"
#include "SFML/Graphics/Sprite.hpp"

inline sf::Sprite get_sprite_from_json(
    const sf::Texture &texture, nlohmann::json &status,
    int recLeft, int recTop, const int sprite_width, const int sprite_height,
    const unsigned int left_index, const unsigned int top_index) {

    // If it is negative, it means that such a parameter was not found.
    if (recLeft < 0) {
        // left_index = move left
        const int base = status["recLeft"]["base"].get<int>();
        const int increase = status["recLeft"]["increase"].get<int>();
        recLeft = base + increase * left_index;
    }
    // If it is negative, it means that such a parameter was not found.
    if (recTop < 0) {
        // facial_expression = move down
        const int base = status["recTop"]["base"].get<int>();
        const int increase = status["recTop"]["increase"].get<int>();
        recTop = base + increase * top_index;
    }

    const sf::IntRect rect(recLeft, recTop, sprite_width, sprite_height);
    sf::Sprite sprite(texture, rect);
    sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);
    return sprite;
}

#endif //PACMAN_FUNC_GET_SPRITE_FROM_JSON_H