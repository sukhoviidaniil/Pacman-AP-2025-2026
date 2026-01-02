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
        const std::string &name, float size, const infra::math::Point2 &position,
        std::unique_ptr<collision::HitBox> hitbox, const float base_speed, const float frightened_speed, ai::GhostAI ai, const std::size_t self_index
        ) : Actor(name, size, position, std::move(hitbox), infra::math::Direction::Down, base_speed), mode_(ai::GhostMode::Scatter), frightened_speed_(frightened_speed),
            ai_(std::move(ai)), self_index_(self_index) {
        permission_ = Permission::High;
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
        std::optional<TilePos> pos = g_ctx.map.get_TilePos(position());
        if (!pos.has_value()) return;
        TilePos self_pos = pos.value();
        ai::UniqGhostContext u_ctx{
            .permission = permission(),
            .mode = mode_,
            .self_pos = self_pos,
            .self_direction = current_direction_,
            .self_index = self_index_
        };
        next_direction_ = ai_.decide(g_ctx, u_ctx);
        move(deltaTime, g_ctx.map);
    }
}
