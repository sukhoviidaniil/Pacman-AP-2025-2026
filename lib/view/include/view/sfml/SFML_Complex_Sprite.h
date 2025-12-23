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

#include "infra/Status.h"
#include "infra/math/Direction.h"
#include "SFML/Graphics/Sprite.hpp"

namespace view {
    class SFML_Complex_Sprite {

    public:
        explicit SFML_Complex_Sprite(const
            std::unordered_map<
                infra::Status,
                std::unordered_map<
                    infra::math::Direction,
                    // animation
                    std::vector<
                        sf::Sprite
                    >
                >
            > & data);

        [[nodiscard]] sf::Sprite &sprite(infra::Status status, infra::math::Direction dir, std::size_t frame);
        [[nodiscard]] const sf::Sprite &sprite(infra::Status status, infra::math::Direction dir, std::size_t frame) const;

    private:
        std::unordered_map<
            infra::Status,
            std::unordered_map<
                infra::math::Direction,
                // animation
                std::vector<
                    sf::Sprite
                >
            >
        > sprites_;
    };
}

#endif //PACMAN_SFML_COMPLEX_SPRITE_H