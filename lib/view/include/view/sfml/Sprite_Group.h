/***************************************************************
 * Project:       Pacman
 * File:          Sprite_Group.h
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
#ifndef PACMAN_SPRITE_GROUP_H
#define PACMAN_SPRITE_GROUP_H

#include <memory>

#include "math/Vector2.h"
#include "SFML/graphics.hpp"
#include <unordered_map>
#include <vector>

#include "model/entity/Actor.h"

namespace view {
    // Used for Entities like Ghosts
    // Hold FULL info about render of this ONE Entity
    class Sprite_Group {
        std::vector<
            // key - status of Sprite;
            std::unordered_map<
                // key - direction of Sprite;
                math::Vector2,
                // animation
                std::vector<
                    sf::Sprite
                >,
                // custom hash function
                math::Vector2Hash
            >
        > entity_sprites_;

        public:

        explicit Sprite_Group(const std::vector<std::unordered_map<math::Vector2,std::vector<sf::Sprite>,math::Vector2Hash>>& data);

        void render(sf::RenderWindow& window, const std::shared_ptr<model::entity::Actor>& actor);
    };
}

#endif //PACMAN_SPRITE_GROUP_H