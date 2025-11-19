/***************************************************************
 * Project:       Pacman
 * File:          DeltaTimer.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-15
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
#include "logic/DeltaTimer.h"

namespace Logic {
    DeltaTimer::DeltaTimer() {
        last = clock::now();
    }

    float DeltaTimer::tick()  {
        const auto now = clock::now();
        const std::chrono::duration<float> diff = now - last;
        last = now;
        return diff.count(); // seconds
    }
}
