/***************************************************************
 * Project:       Pacman
 * File:          Game_Model.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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
#ifndef PACMAN_GAME_MODEL_H
#define PACMAN_GAME_MODEL_H

#include "Score.h"
#include "Tile_Grid.h"
#include "collision/World_Collision_Manager.h"

#include "entity/Pacman.h"

namespace model {
    class Game_Model {
        std::shared_ptr<Score> score;
        std::shared_ptr<Tile_Grid> grid_;
        std::shared_ptr<entity::Pacman> pacman_; // TODO Add Pacman class
        std::unordered_map<
            std::string,
            std::shared_ptr<entity::Actor>
        > ghosts_; // TODO Add Ghost class

        std::vector<
            std::shared_ptr<entity::Actor>
        > coins_; // TODO Add Coin Class

        std::vector<
            std::shared_ptr<entity::Actor>
        > fruits_; // TODO Add Fruit Class

        public:
    };
}

#endif //PACMAN_GAME_MODEL_H