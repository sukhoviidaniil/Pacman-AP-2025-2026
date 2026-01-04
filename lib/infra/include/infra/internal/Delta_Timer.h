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

    /**
     * @brief Utility class to measure elapsed time between updates.
     *
     * Uses a steady clock to compute the delta time since the last tick.
     */
    class Delta_Timer {
        using clock = std::chrono::steady_clock;
        clock::time_point last; ///< Last recorded time point
    public:
        /**
         * @brief Constructs the Delta_Timer and initializes the last time point.
         */
        Delta_Timer();

        /**
         * @brief Returns the time elapsed (in seconds) since the last tick
         *        and updates the internal time point.
         *
         * @return Delta time in seconds.
         */
        float tick();
    };
}

#endif //PACMAN_DELTATIMER_H