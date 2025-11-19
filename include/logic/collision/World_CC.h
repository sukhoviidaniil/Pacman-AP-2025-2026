/***************************************************************
 * Project:       Pacman
 * File:          World_CC.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-18
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
#ifndef PACMAN_WORLD_CC_H
#define PACMAN_WORLD_CC_H
#include "Separating_Axis_Theorem.h"

namespace Logic::Collision {

    class World_CC final : public Separating_Axis_Theorem {
        std::vector<std::vector<int>> world_;
        size_t height_, width_;
        public:
        using Separating_Axis_Theorem::collision;

        World_CC();
        explicit World_CC(const std::vector<std::vector<int>> &vector);
        World_CC(size_t height, size_t width);

        ~World_CC() override;

        bool collision(const HitBoxe_Shape& entity);
    };
}

#endif //PACMAN_WORLD_CC_H