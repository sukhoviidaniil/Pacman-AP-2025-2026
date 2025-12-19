/***************************************************************
 * Project:       Pacman
 * File:          Size.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-19
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
#ifndef PACMAN_SIZE_H
#define PACMAN_SIZE_H

namespace infra::ui {
    struct Size {
        enum class Type { Auto, Pixel, Percent };
        Type  type = Type::Auto;
        float value = 0.f;

        static Size auto_()            { return {}; }
        static Size px(float v)        { return {Type::Pixel, v}; }
        static Size percent(float v)   { return {Type::Percent, v}; }
    };
}

#endif //PACMAN_SIZE_H