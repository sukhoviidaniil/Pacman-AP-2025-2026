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
#include "infra/event/Event_Store.h"

namespace model {
    class Model {
        public:

        explicit Model (const infra::ast::Model& m);

        void run(float delta);

        infra::event::Event_Store event_store_;
        private:
        std::vector<std::shared_ptr<entity::Coin>> coins;
        std::vector<std::shared_ptr<entity::Ghost>> ghosts;
        std::shared_ptr<entity::Pacman> pacman;
        std::shared_ptr<Tile_Grid> grid;
        collision::World_Collision_Manager wcm_;
    };
}

#endif //PACMAN_MODEL_H