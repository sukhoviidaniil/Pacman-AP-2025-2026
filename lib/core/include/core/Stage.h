/***************************************************************
 * Project:       Pacman
 * File:          Stage.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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
#ifndef PACMAN_STAGE_H
#define PACMAN_STAGE_H

#include "infra/Event_Bus.h"

namespace model {
    class Stage {
    public:
        infra::Event_Bus eventbus_; // LOCAL
        Stage();
        virtual ~Stage();
        virtual void run(float tick) = 0;
    };
}

#endif //PACMAN_STAGE_H