/***************************************************************
 * Project:       Pacman
 * File:          Stage_Game.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-24
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

#include "core/stage/Stage_Game.h"


namespace core {
    /*
    Stage_Game::Stage_Game(
        const std::shared_ptr<Game_Model> &game_model,
        const std::shared_ptr<collision::World_Collision_Manager> &WCM
        ) : game_model_(game_model), WCM_(WCM){


    }
    */

    Stage_Game::~Stage_Game() = default;


    void Stage_Game::simulate(float delta) {
        // TODO FULL REWORK
        /*
        // Iteration through all types
        for (auto& [type, vec] : models_by_type){
            // Go through each View in the type
            for (auto& model_ptr : vec){
                if (!model_ptr) continue; // nullptr protection
                // model_ptr->simulate(delta, WCM_); TODO
            }
        }
        */
    }
}
