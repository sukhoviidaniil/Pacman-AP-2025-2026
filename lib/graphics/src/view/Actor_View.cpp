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


#include "graphics/view/Actor_View.h"

namespace Graphics::View {
    Math::Vector2 Actor_View::get_position() const {
        return actor_model_->get_position();
    }

    Actor_View::Actor_View(const std::shared_ptr<Sprite_Group> &sprite):
    sprite_(sprite){

    }

    void Actor_View::set_actor_model(const std::shared_ptr<Logic::Model::Actor> &actor_model) {
        actor_model_ = actor_model;
    }

    void Actor_View::render(sf::RenderWindow& window, const Math::Vector2 &pixel_pos) const {
        if (actor_model_ == nullptr) return;

        sprite_->render(window, pixel_pos, actor_model_->get_direction(), actor_model_->get_status());

    }
}

