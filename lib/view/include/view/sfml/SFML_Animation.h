/***************************************************************
 * Project:       Pacman
 * File:          SFML_Animation.h
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
#ifndef PACMAN_SFML_ANIMATION_H
#define PACMAN_SFML_ANIMATION_H

#include "view/sfml/SFML_Sprite.h"

namespace view {
    class SFML_Animation : public ISFML_Sprite{
    public:
        ~SFML_Animation() override;
        SFML_Animation(int frames_size, float frame_duration, std::vector<sf::Sprite> animation);

        void elapsed(float delta) override;

        [[nodiscard]] size_t index() const;

        [[nodiscard]] sf::Sprite sprite() override;

    private:
        int frames_size_ = 1;
        float frame_duration_ = 0.0f;
        float elapsed_ = 0.f;
        std::vector<
            sf::Sprite
        > animation_;
    };
}

#endif //PACMAN_SFML_ANIMATION_H