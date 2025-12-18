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
#include "infra/ast/view/Drawable.h"

namespace core {
    class Stage {
    public:
        Stage();
        virtual ~Stage();
        virtual void run(float tick) = 0;
        virtual infra::ast::Scene_Graph get_Scene_Graph() const = 0;
        infra::Event_Bus eventbus_; // LOCAL
    };
}

#endif //PACMAN_STAGE_H