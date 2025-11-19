/***************************************************************
 * Project:       Pacman
 * File:          DeltaTimer.h
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
#ifndef PACMAN_DELTATIMER_H
#define PACMAN_DELTATIMER_H
#include <chrono>

namespace Logic {
    class DeltaTimer {
    public:
        using clock = std::chrono::steady_clock;
        DeltaTimer();
        float tick();
    private:
        clock::time_point last;
    };
}

#endif //PACMAN_DELTATIMER_H