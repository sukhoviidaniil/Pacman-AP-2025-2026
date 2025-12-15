/***************************************************************
 * Project:       Pacman
 * File:          Game_View.h
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
#ifndef PACMAN_GAME_VIEW_H
#define PACMAN_GAME_VIEW_H
#include <iostream>

#include "infra/Observer.h"
#include "model/Game_Model.h"
#include "model/Stage.h"

namespace view {
    struct PacmanMoved {};
    class Game_View : public infra::Observer {

    public:
        explicit Game_View(const std::shared_ptr<model::Game_Model>& model) : model_(model) {

        }

        void bind(const std::shared_ptr<model::Stage>& stage) {
            un_track_all();
            track(
                stage->event_bus_.subscribe<PacmanMoved>(
                [this](...) {
                    this->foo();
                }
                , 10
                )
            );
        }

        void foo() {
            std::cout << "Foo" << std::endl;
        }


    private:
        std::shared_ptr<model::Game_Model> model_;
    };
}

#endif //PACMAN_GAME_VIEW_H
