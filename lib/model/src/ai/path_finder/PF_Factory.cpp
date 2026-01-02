/***************************************************************
 * Project:       Pacman
 * File:          PF_Factory.cpp
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

#include "model/ai/path_finder/PF_Factory.h"

#include "infra/diagnostics/Logger.h"
#include "model/ai/path_finder/AStarPathFinder.h"
#include "model/ai/path_finder/BFSPathFinder.h"
#include "model/ai/path_finder/GreedyPathFinder.h"

namespace model::ai{
    std::unique_ptr<model::ai::IPathFinder> PF_Factory::make(const infra::ast::PathFinderType &type) {
        switch (type) {
            case infra::ast::PathFinderType::AStar : {
                return std::make_unique<model::ai::AStarPathFinder>();
            }
            case infra::ast::PathFinderType::BFS : {
                return std::make_unique<model::ai::BFSPathFinder>();
            }
            case infra::ast::PathFinderType::Greedy : {
                return std::make_unique<model::ai::GreedyPathFinder>();
            }
            default: {
                std::string msg = "PF_Factory::make specifies an unknown PathFinder type - the default type is returned.";
                LOG(msg);
            }
        }
        return std::make_unique<model::ai::BFSPathFinder>();
    }
}


