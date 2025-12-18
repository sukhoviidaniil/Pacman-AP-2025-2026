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

#include "core/Stage.h"
#include "model/collision/World_Collision_Manager.h"

namespace core {
    class Stage_Game : public Stage {
    public:
        explicit Stage_Game();
        ~Stage_Game() override;

        void simulate(float delta);
    private:
        std::shared_ptr<model::collision::World_Collision_Manager> WCM_;
    };
}

#endif //PACMAN_STAGE_GAME_H