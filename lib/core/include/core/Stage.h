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

#include "infra/event/Event_Bus.h"
#include "view/presentation/render/RenderFrame.h"

namespace core {
    class Stage {
    public:
        virtual ~Stage();

        explicit Stage(const std::shared_ptr<infra::event::Event_Bus>& eventbus);

        virtual void run(float tick) = 0;

        [[nodiscard]] virtual view::ui::RenderFrame get_RenderFrame(const infra::math::Vector2& screen_size, bool redraw) const = 0;

        std::shared_ptr<infra::event::Event_Bus> eventbus_; /// Local Event Bus
    };
}

#endif //PACMAN_STAGE_H