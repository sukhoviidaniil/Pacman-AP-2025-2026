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

#include "core/Stage_Game.h"

namespace Core {

    Stage_Game::Stage_Game(const std::shared_ptr<World> &world) : world_(world) {
    }

    Stage_Game::~Stage_Game() = default;

    void Stage_Game::simulate(float delta) {
    }

    void Stage_Game::render(sf::RenderWindow& window) {

    }
}
