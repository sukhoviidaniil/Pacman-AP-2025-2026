/***************************************************************
 * Project:       Pacman
 * File:          Entity_Controller.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-10
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
#ifndef PACMAN_ENTITY_CONTROLLER_H
#define PACMAN_ENTITY_CONTROLLER_H

#include "core/Controller.h"
#include "logic/model/Entity.h"
#include <memory>

namespace core::control {
    class Entity_Controller : public Controller {
    public:
        ~Entity_Controller() override;
        void respond(const sf::Event &event) override;

    private:
        std::shared_ptr<logic::model::Entity> entity;
    };
}


#endif //PACMAN_ENTITY_CONTROLLER_H