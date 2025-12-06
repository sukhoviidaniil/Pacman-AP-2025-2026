/***************************************************************
 * Project:       Pacman
 * File:          Stage.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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
#ifndef PACMAN_STAGE_H
#define PACMAN_STAGE_H

#include "SFML/Graphics/RenderWindow.hpp"


namespace Core {
    struct Stage_Info {
        std::string name = "default";
        std::string configuration = "default";
    };
    class Stage {
        public:
        Stage();
        virtual ~Stage();

        virtual void simulate(float delta) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
    };
}

#endif //PACMAN_STAGE_H