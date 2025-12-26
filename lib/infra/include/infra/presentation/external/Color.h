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
        std::uint8_t r = 255, g = 255, b = 255;
        std::uint8_t a = 255;
        Color() = default;
        Color(const std::uint8_t red, const  std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255) : r(red), g(green), b(blue), a(alpha) {}
    };
}


#endif //PACMAN_COLOR_H