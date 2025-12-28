/***************************************************************
 * Project:       Pacman
 * File:          PowerPellet.h
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
#ifndef PACMAN_POWERPELLET_H
#define PACMAN_POWERPELLET_H
#include "Entity.h"

namespace model::entity {
    class PowerPellet : public Entity{
    public:
        ~PowerPellet() override;

        PowerPellet(std::string name, float size, const infra::math::Point2 &position,
                    std::unique_ptr<collision::HitBox> hitbox, float buff_duration_);

        [[nodiscard]] float buff_duration() const;


    private:
        float buff_duration_;
    };
}

#endif //PACMAN_POWERPELLET_H