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

#include "entity/Coin.h"
#include "entity/Pacman.h"
#include "entity/Ghost.h"

namespace model {
    class Model {
        public:
        protected:


        private:
        std::shared_ptr<Tile_Grid> grid;
        std::shared_ptr<entity::Pacman> pacman;
        std::vector<std::shared_ptr<entity::Ghost>> ghosts;
        std::vector<std::shared_ptr<entity::Coin>> coins;
    };
}

#endif //PACMAN_MODEL_H