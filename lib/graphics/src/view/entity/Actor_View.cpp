/***************************************************************
 * Project:       Pacman
 * File:          Actor_View.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-24
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

#include "graphics/view/entity/Actor_View.h"

namespace Graphics::View {


    Actor_View::Actor_View(const std::shared_ptr<Sprite_Group> &sprite):
    sprite_(sprite){

    }

    void Actor_View::render(sf::RenderWindow& window, const Math::Vector2 &pixel_pos) const {
        if (entity_ == nullptr) return;

        sprite_->render(window, pixel_pos, entity_->get_direction(), entity_->get_status());
    }
}

