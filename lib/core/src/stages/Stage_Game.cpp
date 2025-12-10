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

#include "core/stages/Stage_Game.h"
#include "core/stages/World.h"

namespace Core {

    Stage_Game::Stage_Game(const std::shared_ptr<World> &world) : world_(world) {
    }

    Stage_Game::~Stage_Game() = default;

    void Stage_Game::add_Model(const std::string &type, const std::shared_ptr<Model> &model) {
        throw std::runtime_error("Stage_Game::add_Model()");
    }

    std::vector<std::shared_ptr<Model>> Stage_Game::get_Models(const std::string &type) const {
        throw std::runtime_error("Stage_Game::get_Models()");
    }

    std::shared_ptr<Model> Stage_Game::get_Model(const std::string &type, const std::string &name) const {
        throw std::runtime_error("Stage_Game::get_Model()");
    }

    void Stage_Game::add_View(const std::string &type, const std::shared_ptr<View> &view) {
        throw std::runtime_error("Stage_Game::add_View()");
    }

    std::vector<std::shared_ptr<View>> Stage_Game::get_Views(const std::string &type) const {
        throw std::runtime_error("Stage_Game::get_Views()");
    }

    std::shared_ptr<View> Stage_Game::get_View(const std::string &type, const std::string &name) const {
        throw std::runtime_error("Stage_Game::get_View()");
    }

    void Stage_Game::simulate(float delta) {
        world_->simulate(delta);
    }

    void Stage_Game::render(sf::RenderWindow& window) {
        world_->render(window);
    }
}
