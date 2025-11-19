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
#include <memory>

#include "Separating_Axis_Theorem.h"
#include "logic/Tile_Grid.h"

namespace Logic::Collision {

    class World_CC final : public Separating_Axis_Theorem {
        std::shared_ptr<Tile_Grid> world_;
        unsigned int height_ = 0, width_ = 0;
        public:
        explicit World_CC(const std::shared_ptr<Tile_Grid> &world);
        ~World_CC() override;

        using Separating_Axis_Theorem::collision;
        bool collision(const std::shared_ptr<HitBoxe>& entity);
    };
}

#endif //PACMAN_WORLD_CC_H