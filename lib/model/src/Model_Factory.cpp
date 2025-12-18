/***************************************************************
 * Project:       Pacman
 * File:          Model_Factory.cpp
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

#include "model/Model_Factory.h"

#include <memory>

#include "infra/ast/model/Grid.h"
#include "model/Tile_Grid.h"
#include "model/collision/HitBox_Rectangle.h"

namespace model {
    std::shared_ptr<collision::HitBox_Rectangle> make_HitBox_Rectangle(float tile_size) {
        return
    }

    std::shared_ptr<entity::Tile> Model_Factory::make_tile(const math::Point2& position, const std::string& name, float tile_size) {

    };

    std::shared_ptr<Tile_Grid> Model_Factory::make_grid(const infra::ast::Grid &grid_info){

    }
}
