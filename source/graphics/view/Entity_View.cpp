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

    View::Entity_View::~Entity_View() = default;

    Math::Vector2 View::Entity_View::get_position() const {
        return entity_->get_position();
    }
}
