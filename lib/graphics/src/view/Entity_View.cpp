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

#include "graphics/view/Entity_View.h"

namespace Graphics {
    View::Entity_View::Entity_View() = default;

    View::Entity_View::Entity_View(std::string name) : View(std::move(name)) {
    }

    View::Entity_View::Entity_View(const std::shared_ptr<Logic::Model::Entity> &entity){
        set_Entity(entity);
        name_ = entity->get_name();
    }

    View::Entity_View::~Entity_View() = default;

    Math::Vector2 View::Entity_View::get_position() const {
        if (entity_ == nullptr) throw std::invalid_argument("Entity is null");
        return entity_->get_position();
    }

    std::shared_ptr<Logic::Model::Entity> View::Entity_View::get_Entity() const {
        return entity_;
    }


    void View::Entity_View::set_Entity(const std::shared_ptr<Logic::Model::Entity> &entity) {
        if (entity == nullptr) throw std::invalid_argument("Entity is null");
        entity_ = entity;
    }
}
