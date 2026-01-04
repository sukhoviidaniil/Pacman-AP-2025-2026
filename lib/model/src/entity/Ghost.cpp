/***************************************************************
 * Project:       Pacman
 * File:          Ghost.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-02
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

#include "model/entity/Ghost.h"

namespace model::entity {
    Ghost::~Ghost() = default;

    Ghost::Ghost(
        const ai::GhostRole role,
        const float size,
        const infra::math::Point2 &position,
        std::unique_ptr<collision::HitBox> hitbox,
        const float base_speed,
        const float frightened_speed,
        const float dead_speed,
        ai::GhostAI ai,
        const std::size_t self_index
        ) : Actor(ai::role_name(role), size, position, std::move(hitbox), infra::math::Direction::Down, base_speed),
        role_(role),
        mode_(ai::GhostMode::Scatter), frightened_speed_(frightened_speed), dead_speed_(dead_speed),
        ai_(std::move(ai)), self_index_(self_index)
    {
        permission_ = Permission::High;
    }

    void Ghost::be_weak(float debuff_duration) {
        if (is_dead()) return;
        mode_ = ai::GhostMode::Frightened;
        elapsed_ = 0;
        debuff_duration_ = debuff_duration;
    }

    bool Ghost::is_dead() const {
        return mode_ == ai::GhostMode::Dead;
    }
    bool Ghost::is_weak() const {
        return mode_ == ai::GhostMode::Frightened;
    }

    float Ghost::debuff_duration() const {
        return debuff_duration_ - elapsed_;
    }

    void Ghost::reset_elapsed() {
        elapsed_ = 0;
    }

    void Ghost::die() {
        permission_ = Permission::Full;
        mode_ = ai::GhostMode::Dead;
    }

    infra::Status GhostMode_To_Status(const ai::GhostMode& mode) {
        switch (mode) {
            case ai::GhostMode::Chase : return infra::Status::Alive;
            case ai::GhostMode::Dead : return infra::Status::Dead;
            case ai::GhostMode::Frightened : return infra::Status::Weak;
            case ai::GhostMode::Scatter : return infra::Status::SlightlyWeak;
            default: return infra::Status::Alive;
        }
    }

    void Ghost::act(const float deltaTime, const ai::GlobalGhostContext &g_ctx) {
        change_mode(deltaTime, g_ctx);

        const std::optional<TilePos> pos = g_ctx.map.get_TilePos(position());
        if (!pos.has_value()) return;
        const TilePos self_pos = pos.value();

        if (mode_ == ai::GhostMode::Dead) {
            if (const Tile tile = g_ctx.map.get_tile(self_pos); tile == Tile::GhostSpawn) {
                elapsed_ = 0.f;
                mode_ = ai::GhostMode::Scatter;
                permission_ = Permission::High;
            }
        }

        if (g_ctx.map.can_choose_direction(self_pos, current_direction_, permission())) {
            ai::UniqGhostContext u_ctx{
                .permission = permission(),
                .mode = mode_,
                .self_pos = self_pos,
                .self_direction = current_direction_,
                .self_index = self_index_
            };

            next_direction_ = ai_.decide(g_ctx, u_ctx);
        }

        move(deltaTime, g_ctx.map);
    }

    float Ghost::speed() const {
        switch (mode_){
            case ai::GhostMode::Frightened : {
                return frightened_speed_;
            }
            case ai::GhostMode::Dead : {
                return dead_speed_;
            }
            default: return speed_;
        }
    }

    void Ghost::change_mode(float deltaTime, const ai::GlobalGhostContext &g_ctx) {
        elapsed_ += deltaTime;

        if (mode_ == ai::GhostMode::Dead) return;

        // --- 1. Frightened has priority ---
        if (mode_ == ai::GhostMode::Frightened) {
            if (debuff_duration()<= 0.f) {
                debuff_duration_ = 0;
                elapsed_ = 0.f;
                mode_ = ai::GhostMode::Scatter;

                // forced reverse
                current_direction_ = infra::math::opposite(current_direction_);
                next_direction_ = current_direction_;
            }
            return;
        }

        // --- 2. Scatter / Chase timings (Level 1 example) ---
        struct Phase { float duration; ai::GhostMode mode; };
        static const Phase phases[] = {
            { 5.f,  ai::GhostMode::Scatter },
            { 15.f, ai::GhostMode::Chase   },
            { 5.f,  ai::GhostMode::Scatter },
            { 20.f, ai::GhostMode::Chase   },
            { 3.f,  ai::GhostMode::Scatter },
            { -1.f, ai::GhostMode::Chase } // inf
        };

        float t = elapsed_;
        for (const auto& p : phases) {
            if (p.duration < 0.f || t < p.duration) {
                if (mode_ != p.mode) {
                    mode_ = p.mode;
                    // forced reverse on mode switch
                    current_direction_ = infra::math::opposite(current_direction_);
                    next_direction_ = current_direction_;
                }
                break;
            }
            t -= p.duration;
        }
    }
}
