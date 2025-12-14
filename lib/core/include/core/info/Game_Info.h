/***************************************************************
 * Project:       Pacman
 * File:          Game_Info.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-02
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
#ifndef PACMAN_GAME_INFO_H
#define PACMAN_GAME_INFO_H

#include <string>

namespace core {
    struct Game_Info {
        std::string graphics = "not SFML";
        int window_width = -1;
        int window_height = -1;
        std::string graphics_conf = "wrong_path_no_conf.json";
        std::string stage_mng = "wrong_path_no_conf.json";
    };
}

#endif //PACMAN_GAME_INFO_H