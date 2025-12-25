/***************************************************************
 * Project:       Pacman
 * File:          Color.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-22
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
#ifndef PACMAN_COLOR_H
#define PACMAN_COLOR_H

#include <cstdint>
namespace infra::ui {

    struct Color {
        std::uint8_t r, g, b;
        std::uint8_t a = 255;
    };
}


#endif //PACMAN_COLOR_H