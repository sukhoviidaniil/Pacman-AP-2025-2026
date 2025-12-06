/***************************************************************
 * Project:       Pacman
 * File:          View.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-06
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
#ifndef PACMAN_VIEW_H
#define PACMAN_VIEW_H

#include "logic/model/Entity.h"
#include "math/Vector2.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include <memory>
#include <string>

namespace Graphics::View {
    class View {
    protected:
        std::string name_ = "None";
    public:
        View();
        explicit View(std::string  name);
        virtual ~View();

        [[nodiscard]] virtual std::string get_name() const;
        [[nodiscard]] virtual Math::Vector2 get_position() const = 0;
        [[nodiscard]] virtual std::shared_ptr<Logic::Model::Entity> get_Entity() const = 0;

        virtual void render(sf::RenderWindow &window, const Math::Vector2& pixel_pos) const = 0;
    };
}

#endif //PACMAN_VIEW_H