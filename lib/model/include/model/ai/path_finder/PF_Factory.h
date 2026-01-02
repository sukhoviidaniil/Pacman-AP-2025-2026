/***************************************************************
 * Project:       Pacman
 * File:          PF_Factory.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-01
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
#ifndef PACMAN_PF_FACTORY_H
#define PACMAN_PF_FACTORY_H
#include <memory>

#include "IPathFinder.h"
#include "infra/ast/model/GhostSpawn.h"

namespace model::ai {
    class PF_Factory {
        static std::unique_ptr<IPathFinder> make(const infra::ast::PathFinderType& type);
    };
}

#endif //PACMAN_PF_FACTORY_H