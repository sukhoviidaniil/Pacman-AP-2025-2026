/***************************************************************
 * Project:       Pacman
 * File:          Score.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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
#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H

#include "infra/event/Observer.h"

namespace core {
    class Score : public infra::event::Observer {
        unsigned int lives_remaining = 3;
        unsigned int points_score = 0;
        public:
        Score();
        ~Score() override;
        virtual void track_local(const std::shared_ptr<infra::event::Event_Bus>& bus);

    };
}

#endif //PACMAN_SCORE_H
