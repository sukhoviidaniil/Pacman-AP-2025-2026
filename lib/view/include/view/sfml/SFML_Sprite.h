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
        [[nodiscard]] virtual sf::Sprite &sprite() = 0;
        [[nodiscard]] virtual const sf::Sprite &sprite() const = 0;

    };
    struct SFML_Sprite : ISFML_Sprite{
        sf::Sprite sprite_;
        explicit SFML_Sprite(sf::Sprite sprite) : sprite_(std::move(sprite)) {}

        [[nodiscard]] sf::Sprite &sprite() override {
            return sprite_;
        }
        [[nodiscard]]const sf::Sprite &sprite() const override {
            return sprite_;
        }

    };


}

#endif //PACMAN_SFML_SPRITE_H