/***************************************************************
 * Project:       Pacman
 * File:          Stage_Game.h
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
#ifndef PACMAN_STAGE_GAME_H
#define PACMAN_STAGE_GAME_H

#include <memory>

#include "model/Game_Model.h"
#include "../../../../core/include/core/Stage.h"

namespace model::stage {
    class Stage_Game : public Stage {
    public:
        explicit Stage_Game(const std::shared_ptr<Game_Model> &game_model, const std::shared_ptr<collision::World_Collision_Manager> &WCM);
        ~Stage_Game() override;

        void simulate(float delta);
    private:
        std::shared_ptr<Game_Model> game_model_;
        std::shared_ptr<collision::World_Collision_Manager> WCM_;
    };
}

#endif //PACMAN_STAGE_GAME_H