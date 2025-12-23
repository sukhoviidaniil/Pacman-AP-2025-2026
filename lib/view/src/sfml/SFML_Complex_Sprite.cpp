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
        const std::unordered_map<infra::Status, std::unordered_map<infra::math::Direction, std::vector<sf::Sprite>>> &
        data) : sprites_(data){
    }



    sf::Sprite& SFML_Complex_Sprite::sprite(
        infra::Status status,
        infra::math::Direction dir,
        std::size_t frame = 0
    ) {
        return sprites_.at(status).at(dir).at(frame);
    }


    const sf::Sprite& SFML_Complex_Sprite::sprite(
        infra::Status status,
        infra::math::Direction dir,
        std::size_t frame = 0
    ) const {
        return sprites_.at(status).at(dir).at(frame);
    }
}
