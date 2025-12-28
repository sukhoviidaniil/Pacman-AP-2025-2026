/***************************************************************
 * Project:       Pacman
 * File:          PowerPellet.cpp
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

#include "model/entity/PowerPellet.h"

namespace model::entity {
    PowerPellet::~PowerPellet() = default;
    PowerPellet::PowerPellet(std::string name, float size, const infra::math::Point2 &position, std::unique_ptr<collision::HitBox> hitbox,
        const float buff_duration_) : Entity(name, size, position, std::move(hitbox)), buff_duration_(buff_duration_) {
    }

    float PowerPellet::buff_duration() const {
        return buff_duration_;
    }
}
