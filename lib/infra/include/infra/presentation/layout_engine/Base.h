/***************************************************************
 * Project:       Pacman
 * File:          Base.h
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
#ifndef PACMAN_BASE_H
#define PACMAN_BASE_H

#pragma once
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>
#include <cassert>

namespace infra::ui {
    struct Vec2 {
        float x = 0, y = 0;
    };

    struct Rect {
        float x, y, w, h;
    };
}
#endif //PACMAN_BASE_H