/***************************************************************
 * Project:       Pacman
 * File:          Entity_View.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-20
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

/*
#include "graphics/view/Entity_View.h"

namespace graphics {
    view::Entity_View::Entity_View() = default;

    view::Entity_View::Entity_View(std::string name) : View(std::move(name)) {
    }

    view::Entity_View::Entity_View(const std::shared_ptr<logic::model::Entity> &entity){
        set_Entity(entity);
        name_ = entity->get_name();
    }

    view::Entity_View::~Entity_View() = default;

    math::Vector2 view::Entity_View::get_position() const {
        if (entity_ == nullptr) throw std::invalid_argument("Entity is null");
        return entity_->get_position();
    }

    std::shared_ptr<logic::model::Entity> view::Entity_View::get_Entity() const {
        return entity_;
    }


    void view::Entity_View::set_Entity(const std::shared_ptr<logic::model::Entity> &entity) {
        if (entity == nullptr) throw std::invalid_argument("Entity is null");
        entity_ = entity;
    }
}
*/