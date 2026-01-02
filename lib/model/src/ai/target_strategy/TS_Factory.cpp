/***************************************************************
 * Project:       Pacman
 * File:          TS_Factory.cpp
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

#include "model/ai/target_strategy/TS_Factory.h"

#include "infra/internal/Random.h"
#include "model/ai/target_strategy/BlinkyTarget.h"
#include "model/ai/target_strategy/ClydeTarget.h"
#include "model/ai/target_strategy/CornerTargetStrategy.h"
#include "model/ai/target_strategy/InkyTarget.h"
#include "model/ai/target_strategy/PinkyTarget.h"

namespace model::ai {
    std::unique_ptr<TargetStrategy> TS_Factory::make(const GhostRole &type) {
        switch (type) {
            case GhostRole::Blinky : return std::make_unique<BlinkyTarget>();
            case GhostRole::Pinky : return std::make_unique<PinkyTarget>();
            case GhostRole::Inky : return std::make_unique<InkyTarget>();
            case GhostRole::Clyde : return std::make_unique<ClydeTarget>();
            default: {
                const std::string err = "No TargetStrategy option found for type " + role_name(type);
                throw std::invalid_argument(err);
            }
        }
    }

    std::unique_ptr<TargetStrategy> TS_Factory::make_corner(const TileGrid &map, infra::math::Direction preferred_corner) {
        using namespace infra::math;
        Direction corner_dir = preferred_corner;
        if (corner_dir == Direction::Any || corner_dir == Direction::None || corner_dir == Direction::Unknown) {
            switch (RAND_INT(0, 3)) {
                case 0: corner_dir = Direction::Up; break;
                case 1: corner_dir = Direction::Right; break;
                case 2: corner_dir = Direction::Down; break;
                case 3: corner_dir = Direction::Left; break;
                default: corner_dir = Direction::Up; break;
            }
        }
        return std::make_unique<CornerTargetStrategy>(map, corner_dir);
    }
}
