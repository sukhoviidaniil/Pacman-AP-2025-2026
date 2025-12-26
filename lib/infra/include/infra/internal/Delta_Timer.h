/***************************************************************
 * Project:       Pacman
 * File:          Delta_Timer.h
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

namespace infra {
    class Delta_Timer {
        using clock = std::chrono::steady_clock;
        clock::time_point last;
    public:
        Delta_Timer();
        float tick();
    };
}

#endif //PACMAN_DELTATIMER_H