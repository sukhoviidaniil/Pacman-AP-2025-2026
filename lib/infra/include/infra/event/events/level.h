/***************************************************************
 * Project:       Pacman
 * File:          level.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-27
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
#ifndef PACMAN_EVENTSLEVEL_H
#define PACMAN_EVENTSLEVEL_H

#include "infra/event/Event.h"

namespace infra::event::level {
    struct ButtonPressed {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Level;
        std::size_t index;
        explicit ButtonPressed(const std::size_t index) : index(index) {}
    };
}

#endif //PACMAN_EVENTSLEVEL_H