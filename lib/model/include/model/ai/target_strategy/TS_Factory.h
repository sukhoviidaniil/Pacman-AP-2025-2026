/***************************************************************
 * Project:       Pacman
 * File:          TS_Factory.h
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
#ifndef PACMAN_TS_FACTORY_H
#define PACMAN_TS_FACTORY_H
#include "TargetStrategy.h"
#include "model/ai/internal/GhostRole.h"

namespace model::ai {
    class TS_Factory {
    public:
        static std::unique_ptr<TargetStrategy> make(const GhostRole& type);
        static std::unique_ptr<TargetStrategy> make_corner(const TileGrid &map, infra::math::Direction preferred_corner);
    };
}

#endif //PACMAN_TS_FACTORY_H