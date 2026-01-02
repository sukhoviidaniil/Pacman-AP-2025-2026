/***************************************************************
 * Project:       Pacman
 * File:          Ghost.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-16
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
#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include "model/ai/GhostAI.h"
#include "model/entity/Actor.h"

namespace model::entity {
    class Ghost : public Actor {
    public:
        ~Ghost() override;
        Ghost(
            const std::string &name, float size, const infra::math::Point2 &position,
            std::unique_ptr<collision::HitBox> hitbox, float base_speed, float frightened_speed, ai::GhostAI ai, std::size_t self_index);

        void act(float deltaTime, const ai::GlobalGhostContext& g_ctx);

    private:
        ai::GhostMode mode_;
        float frightened_speed_;
        ai::GhostAI ai_;
        std::size_t self_index_;
    };
}

#endif //PACMAN_GHOST_H