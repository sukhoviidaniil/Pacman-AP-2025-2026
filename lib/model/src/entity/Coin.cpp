/***************************************************************
 * Project:       Pacman
 * File:          Coin.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-28
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

#include "model/entity/Coin.h"
namespace entity {

}

model::entity::Coin::Coin(float size, const infra::math::Point2 &position, std::unique_ptr<collision::HitBox> hitbox) : Entity("Coin", size, position, std::move(hitbox)){
}

model::entity::Coin::~Coin() = default;
