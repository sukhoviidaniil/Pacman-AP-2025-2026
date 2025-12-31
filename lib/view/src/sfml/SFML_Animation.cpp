/***************************************************************
 * Project:       Pacman
 * File:          SFML_Animation.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-28
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

#include "view/sfml/SFML_Animation.h"
namespace view {
    SFML_Animation::~SFML_Animation() = default;

    SFML_Animation::SFML_Animation(const int frames_size, const float frame_duration, std::vector<sf::Sprite> animation) :
    frames_size_(frames_size), frame_duration_(frame_duration), animation_(std::move(animation)) {
    }

    void SFML_Animation::elapsed(const float delta) {
        elapsed_+=delta;
    }

    size_t SFML_Animation::index() const  {
        return static_cast<size_t>(static_cast<int>(elapsed_ / frame_duration_) % frames_size_);
    }

    sf::Sprite SFML_Animation::sprite() {
        sf::Sprite s = animation_[index()];
        s.setPosition(0.f, 0.f);
        s.setScale(1.f, 1.f);
        return s;
    }
}
