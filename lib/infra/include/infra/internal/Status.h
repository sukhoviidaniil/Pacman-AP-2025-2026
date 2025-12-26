/***************************************************************
 * Project:       Pacman
 * File:          Status.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-23
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
#ifndef PACMAN_STATUS_H
#define PACMAN_STATUS_H

namespace infra {
    enum class Status {
        Dead,
        Alive,
        Powered,
        Weak,
        SlightlyWeak
    };
}

#endif //PACMAN_STATUS_H