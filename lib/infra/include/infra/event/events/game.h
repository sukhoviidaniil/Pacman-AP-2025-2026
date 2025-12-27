/***************************************************************
 * Project:       Pacman
 * File:          game.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-25
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
#ifndef PACMAN_EVENTS_GAME_H
#define PACMAN_EVENTS_GAME_H
#include "infra/event/Event.h"

namespace infra::event::game {

    struct Request_StartStage {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_StartStage() = default;
    };

    struct Request_NextLevelStage {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_NextLevelStage() = default;
    };

    struct Request_EnterPause {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_EnterPause() = default;
    };

    struct Request_ExitPause {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_ExitPause() = default;
    };

    struct Request_DeathStage {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_DeathStage() = default;
    };



    struct ButtonPressed {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;
        std::size_t index;
        explicit ButtonPressed(const std::size_t index) : index(index) {}
    };
}

#endif //PACMAN_EVENTS_GAME_H