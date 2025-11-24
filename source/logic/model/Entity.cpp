/***************************************************************
 * Project:       Pacman
 * File:          Entity.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-17
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

#include "logic/model/Entity.h"

namespace Logic::Core {
    Entity::Entity(const Math::Vector2 &position) :position_(position) {
    }
}
