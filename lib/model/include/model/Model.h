/***************************************************************
 * Project:       Pacman
 * File:          Model.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-16
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
#ifndef PACMAN_MODEL_H
#define PACMAN_MODEL_H
#include <future>

#include "infra/ast/model/Model.h"
#include "entity/Coin.h"
#include "entity/Pacman.h"
#include "entity/Ghost.h"

namespace model {
    class Model {
        public:

        explicit Model (const infra::ast::Model& m);

        [[nodiscard]] bool all_coins_collected() const;
        [[nodiscard]] bool all_ghosts_dead() const;


        std::vector<std::shared_ptr<entity::Coin>> coins;
        std::vector<std::shared_ptr<entity::Ghost>> ghosts;
        std::shared_ptr<entity::Pacman> pacman;
        std::shared_ptr<Tile_Grid> grid;
        collision::World_Collision_Manager wcm_;

    };
}

#endif //PACMAN_MODEL_H