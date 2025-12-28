/***************************************************************
 * Project:       Pacman
 * File:          Pacman.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-22
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

#include "model/entity/Pacman.h"

#include "infra/math/Direction.h"

namespace model::entity {
    Pacman::~Pacman() = default;

    Pacman::Pacman(float size, const infra::math::Point2 &position, std::unique_ptr<collision::HitBox> hitbox, float speed)
        : Actor("Pacman", size, position, std::move(hitbox), infra::math::Direction::Right, speed){
    }
}
