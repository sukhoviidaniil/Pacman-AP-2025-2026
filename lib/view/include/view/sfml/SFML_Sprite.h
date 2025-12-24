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
    struct  SFML_Animation : ISFML_Sprite {
        int frames_size_ = 1;
        float frame_duration_ = 0.0f;
        float elapsed_ = 0.f;
        std::vector<
            sf::Sprite
        > animation_; // 1 element if Animation is of

        SFML_Animation();

        void elapsed(const float delta) override{
            elapsed_+=delta;
        }

        [[nodiscard]] size_t index() const {
            return static_cast<size_t>(static_cast<int>(elapsed_ / frame_duration_) % frames_size_);
        }

        [[nodiscard]] sf::Sprite &sprite() override {
            return animation_[index()];

        }

        [[nodiscard]] const sf::Sprite &sprite() const override {
            return animation_[index()];
        }
    };

}

#endif //PACMAN_SFML_SPRITE_H