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

#include "SFML/Graphics/RenderWindow.hpp"
#include "math/Vector2.h"

namespace Graphics::View {
    class Entity_View {
    protected:
        std::string name_ = "None";
    public:
        Entity_View();
        explicit Entity_View(const std::string& name);
        virtual ~Entity_View();

        [[nodiscard]] virtual Math::Vector2 get_position() const = 0;

        virtual void render(sf::RenderWindow &window, const Math::Vector2& pixel_pos) const = 0;
    };
}

#endif //PACMAN_ENTITY_VIEW_H