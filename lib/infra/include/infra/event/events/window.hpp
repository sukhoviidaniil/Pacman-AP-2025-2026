/***************************************************************
 * Project:       Pacman
 * File:          window.hpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-21
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
#ifndef PACMAN_EV_WINDOW_HPP
#define PACMAN_EV_WINDOW_HPP
#include "infra/event/Event.h"


namespace infra::event::window {
    struct Closed{
        static constexpr infra::event::EventMask mask =
            infra::event::EventMask::Window;
    };
    struct Resized {
        static constexpr infra::event::EventMask mask =
            infra::event::EventMask::Window;

        std::uint32_t width;
        std::uint32_t height;
    };

    struct FocusGained {
        static constexpr infra::event::EventMask mask =
            infra::event::EventMask::Window;
    };

    struct FocusLost {
        static constexpr infra::event::EventMask mask =
            infra::event::EventMask::Window;
    };
}

#endif //PACMAN_EV_WINDOW_HPP