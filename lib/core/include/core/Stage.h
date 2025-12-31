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

#include "control/Controller.h"
#include "infra/event/Event_Bus.h"
#include "view/presentation/layout_engine/UIElement.h"
#include "view/presentation/render/RenderFrame.h"

namespace core::stg {
    class Stage {
    public:
        virtual ~Stage() = default;

        explicit Stage(const std::shared_ptr<infra::event::Event_Bus> &globalBus);
        virtual void checkIn();

        virtual void run(float delta) = 0;

        [[nodiscard]] virtual view::ui::RenderFrame get_RenderFrame(const infra::math::Vector2& screen_size, bool redraw) const = 0;

        std::unique_ptr<control::Controller> controller = nullptr; /// Controller of this stage
        std::unique_ptr<infra::event::Event_Bus> l_eventbus; /// Local Event Bus (for local events)
    protected:
        virtual void dispatch(infra::event::Event_Store &event_store);
        std::unique_ptr<view::ui::UIElement> ui_root_ = nullptr; /// Stage UI
        std::shared_ptr<infra::event::Event_Bus> g_eventbus;/// Global Event Bus (for stage change)
    };
}

#endif //PACMAN_STAGE_H