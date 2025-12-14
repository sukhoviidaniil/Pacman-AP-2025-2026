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

#include <memory>

#include "graphics/View.h"

namespace graphics::view {
    class Entity_View : public View {
    protected:
        std::shared_ptr<logic::model::Entity> entity_;
    public:
        Entity_View();
        explicit Entity_View(std::string name);
        explicit Entity_View(const std::shared_ptr<logic::model::Entity>& entity);
        ~Entity_View() override;

        [[nodiscard]] math::Vector2 get_position() const override;
        [[nodiscard]] std::shared_ptr<logic::model::Entity> get_Entity() const override;

        void set_Entity(const std::shared_ptr<logic::model::Entity> &entity);

        void render(sf::RenderWindow &window, const math::Vector2& pixel_pos) const override = 0;
    };
}

#endif //PACMAN_ENTITY_VIEW_H