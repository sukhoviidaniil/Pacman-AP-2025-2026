/***************************************************************
 * Project:       Pacman
 * File:          input_Mouse.h
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
#ifndef PACMAN_INPUT_MOUSE_H
#define PACMAN_INPUT_MOUSE_H
#include <cstdint>

#include "infra/event/Event_Bus.h"

namespace infra::event::input {
    enum class MouseButton : std::uint8_t {
        Left,
        Right,
        Middle,
        XButton1,
        XButton2
    };

    struct MouseMoved {
        static constexpr infra::event::EventMask mask =
            infra::event::EventMask::Input;

        int x;
        int y;
    };

    struct MouseButtonPressed {
        static constexpr infra::event::EventMask mask =
            infra::event::EventMask::Input;

        MouseButton button;
        int x;
        int y;
    };

    struct MouseButtonReleased {
        static constexpr infra::event::EventMask mask =
            infra::event::EventMask::Input;

        MouseButton button;
        int x;
        int y;
    };

    struct MouseWheelScrolled {
        static constexpr infra::event::EventMask mask =
            infra::event::EventMask::Input;

        float delta;
        int x;
        int y;
    };
}

#endif //PACMAN_INPUT_MOUSE_H