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
namespace model::ai {
    std::unique_ptr<TargetStrategy> TS_Factory::make(const GhostRole &type) {
        switch (type) {
            case GhostRole::Blinky : return std::make_unique<>();
            case GhostRole::Pinky : return "Pinky";
            case GhostRole::Inky : return "Inky";
            case GhostRole::Clyde : return "Clyde";
            default: return "None";
        }
    }
}
