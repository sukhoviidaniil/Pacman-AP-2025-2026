/***************************************************************
 * Project:       Pacman
 * File:          SFML_Sprite.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-23
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
#ifndef PACMAN_SFML_SPRITE_H
#define PACMAN_SFML_SPRITE_H
#include <vector>

#include "SFML/Graphics/Sprite.hpp"

namespace view {

    struct ISFML_Sprite {
        virtual ~ISFML_Sprite() = default;

        virtual void elapsed(const float delta) {

        }
        [[nodiscard]] virtual sf::Sprite sprite() = 0;

    };
    struct SFML_Sprite : ISFML_Sprite{
        sf::Sprite sprite_;
        explicit SFML_Sprite(sf::Sprite sprite) : sprite_(std::move(sprite)) {}

        [[nodiscard]] sf::Sprite sprite() override {
            sf::Sprite s = sprite_;
            s.setPosition(0.f, 0.f);
            s.setScale(1.f, 1.f);
            return s;
        }

    };

}

#endif //PACMAN_SFML_SPRITE_H