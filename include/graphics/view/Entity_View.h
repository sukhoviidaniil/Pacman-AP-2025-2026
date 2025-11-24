/***************************************************************
 * Project:       Pacman
 * File:          Entity_View.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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
#ifndef PACMAN_ENTITY_VIEW_H
#define PACMAN_ENTITY_VIEW_H

#include "SFML/Window/Window.hpp"
#include "math/Vector2.h"

#include <memory>

#include "logic/model/Entity.h"

namespace Graphics::View {
    class Entity_View {
        std::shared_ptr<Logic::Core::Entity> entity_;
    public:

        Entity_View();
        virtual ~Entity_View();

        Math::Vector2 get_position() const;

        virtual void render(const Math::Vector2& pixel_pos, const std::shared_ptr<sf::Window> &window) const = 0;
    };
}

#endif //PACMAN_ENTITY_VIEW_H