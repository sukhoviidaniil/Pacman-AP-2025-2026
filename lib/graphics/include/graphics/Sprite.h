/***************************************************************
 * Project:       Pacman
 * File:          Sprite.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-26
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
#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H

#include "math/Vector2.h"

namespace Graphics {
    class Sprite {

        public:
        virtual ~Sprite() = default;

        virtual void set_Position(Math::Vector2 pos) = 0;
    };
}
#endif //PACMAN_SPRITE_H
