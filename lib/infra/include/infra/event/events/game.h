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

    struct ButtonPressed {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;
        std::size_t index;
        explicit ButtonPressed(const std::size_t index) : index(index) {}
    };

    struct Request_StartStage {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_StartStage() = default;
    };

    struct Request_New_LevelStage {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_New_LevelStage() = default;
    };
    struct Request_Continuing_LevelStage {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_Continuing_LevelStage() = default;
    };

    struct Request_EnterPause {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_EnterPause() = default;
    };

    struct Request_ExitPause {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        Request_ExitPause() = default;
    };

    struct All_Coins_Collected {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        All_Coins_Collected() = default;
    };

    struct PacMan_Died {
        static constexpr infra::event::EventMask mask = infra::event::EventMask::Game;

        PacMan_Died() = default;
    };

}

#endif //PACMAN_EVENTS_GAME_H