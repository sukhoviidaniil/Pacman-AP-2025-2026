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

#include "core/Stage.h"
#include <memory>

namespace core {
    class World;
    class Stage_Game : public Stage {
        std::shared_ptr<World> world_;
        public:

        explicit Stage_Game(const std::shared_ptr<World> &world);
        ~Stage_Game() override;

        void add_model(const std::string &type, const std::shared_ptr<logic::model::Entity> &model) override;

        [[nodiscard]] std::vector<std::shared_ptr<logic::model::Entity>> get_models(const std::string &type) const override;

        [[nodiscard]] std::shared_ptr<logic::model::Entity> get_model(const std::string &type, const std::string &name) const override;

        void add_View(const std::string &type, const std::shared_ptr<graphics::View> &view) override;

        [[nodiscard]] std::vector<std::shared_ptr<graphics::View>> get_Views(const std::string &type) const override;

        [[nodiscard]] std::shared_ptr<graphics::View> get_View(const std::string &type, const std::string &name) const override;

        void simulate(float delta) override;
        void render(sf::RenderWindow& window) override;
    };
}

#endif //PACMAN_STAGE_GAME_H