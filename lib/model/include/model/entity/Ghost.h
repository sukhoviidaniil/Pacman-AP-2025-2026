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
#include "model/ai/internal/GhostRole.h"
#include "model/entity/Actor.h"

namespace model::entity {
    class Ghost : public Actor {
    public:
        ~Ghost() override;
        Ghost(
            ai::GhostRole role,
            float size,
            const infra::math::Point2 &position,
            std::unique_ptr<collision::HitBox> hitbox,
            float base_speed,
            float frightened_speed,
            float dead_speed,
            ai::GhostAI ai,
            std::size_t self_index
            );

        void be_weak(float debuff_duration);

        bool is_dead() const;

        [[nodiscard]] bool is_weak() const;
        [[nodiscard]] float debuff_duration() const;
        void reset_elapsed();
        void die();
        void act(float deltaTime, const ai::GlobalGhostContext& g_ctx);

    private:
        [[nodiscard]] float speed() const override;

        void change_mode(float deltaTime, const ai::GlobalGhostContext& g_ctx);
        ai::GhostRole role_;
        ai::GhostMode mode_;
        float frightened_speed_;
        float dead_speed_;
        ai::GhostAI ai_;
        std::size_t self_index_;

        float elapsed_ = 0;
        float debuff_duration_;
    };
}

#endif //PACMAN_GHOST_H