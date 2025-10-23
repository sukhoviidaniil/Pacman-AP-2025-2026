/***************************************************************
 * Project:       Pacman
 * File:          Entity.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-10-23
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
#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include "math/Vector2.h"

class Entity {
    Math::Vector2 position;
    Math::Vector2 current_direction;
    Math::Vector2 next_dir;
    float speed = 1.0;
    float radius = 5.0;
    bool alive = true;
    public:


};

#endif //PACMAN_ENTITY_H