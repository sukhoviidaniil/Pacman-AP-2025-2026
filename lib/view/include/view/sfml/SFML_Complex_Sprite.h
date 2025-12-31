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
#include <memory>
#include <unordered_map>

#include "SFML/Graphics/Sprite.hpp"
#include "infra/math/Direction.h"
#include "infra/internal/Status.h"
#include "view/sfml/SFML_Sprite.h"

namespace view {

    class SFML_Complex_Sprite {
    public:
        explicit SFML_Complex_Sprite(
            std::unordered_map<
                infra::Status,
                std::unordered_map<
                    infra::math::Direction,
                    // animation
                    std::unique_ptr<ISFML_Sprite>
                >
            > data
            );

        void elapsed(float delta) const;
        [[nodiscard]] sf::Sprite sprite(infra::Status status, infra::math::Direction dir);

    private:
        std::unordered_map<
            infra::Status,
            std::unordered_map<
                infra::math::Direction,
                // animation
                std::unique_ptr<ISFML_Sprite>
            >
        > sprites_;
    };
}

#endif //PACMAN_SFML_COMPLEX_SPRITE_H