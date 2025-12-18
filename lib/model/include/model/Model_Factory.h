/***************************************************************
 * Project:       Pacman
 * File:          Model_Factory.h
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
#ifndef PACMAN_MODEL_FACTORY_H
#define PACMAN_MODEL_FACTORY_H
#include "Tile_Grid.h"
#include "infra/ast/Visitor.h"
#include "infra/ast/model/Grid.h"

namespace model {
    class Model_Factory : public infra::ast::Model_Visitor {
    public:
        void visit(const infra::ast::Model&) override;

        std::shared_ptr<entity::Tile> make_tile(const math::Point2 &position, const std::string &name, float tile_size);

        std::shared_ptr<Tile_Grid> make_grid(const infra::ast::Grid &tile_grid_info);
    };
}

#endif //PACMAN_MODEL_FACTORY_H
