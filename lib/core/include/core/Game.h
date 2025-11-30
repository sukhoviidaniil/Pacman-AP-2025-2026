/***************************************************************
 * Project:       Pacman
 * File:          Game.h
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
#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <string>

namespace Core {
    class Game {

        int window_width;
        int window_height;

        public:
        Game();
        static void run(const std::string& path);
    };
}

#endif //PACMAN_GAME_H