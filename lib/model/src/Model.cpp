/***************************************************************
 * Project:       Pacman
 * File:          Model.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-18
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

#include "model/Model.h"

#include "model/collision/Separating_Axis_Theorem.h"

namespace model {
    Model::Model(const infra::ast::Model &m) {
        grid = std::make_shared<Tile_Grid>(m.grid);
        auto sat = std::make_unique<collision::Separating_Axis_Theorem>();
        wcm_ = collision::World_Collision_Manager(std::move(sat), grid);
    }

    void Model::run(float delta) {

    }
}
