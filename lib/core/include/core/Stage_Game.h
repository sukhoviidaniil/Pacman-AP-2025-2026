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


#include "Stage.h"
#include "World.h"
#include <memory>

namespace Core {
    class Stage_Game : Stage {
        std::shared_ptr<World> world_;
        public:

        explicit Stage_Game(const std::shared_ptr<World> &world);
        ~Stage_Game() override;

        void simulate(float delta) override;
        void render(sf::RenderWindow& window) override;
    };
}

#endif //PACMAN_STAGE_GAME_H