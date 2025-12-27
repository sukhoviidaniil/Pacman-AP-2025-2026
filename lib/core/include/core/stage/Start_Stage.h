/***************************************************************
 * Project:       Pacman
 * File:          Start_Stage.h
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
#ifndef PACMAN_START_STAGE_H
#define PACMAN_START_STAGE_H
#include "core/Stage.h"

namespace core::stg {
    class Start_Stage : public Stage {
    public:
        ~Start_Stage() override;
        Start_Stage(
            const std::shared_ptr<infra::event::Event_Bus> &globalBus,
            infra::Const_ScoreBord sb
            );

        void run(float delta) override;

        [[nodiscard]] view::ui::RenderFrame get_RenderFrame(const infra::math::Vector2 &screen_size, bool redraw) const override;

    private:
        std::shared_ptr<infra::menu::Menu> menu_;
        infra::Const_ScoreBord sb_;
    };
}

#endif //PACMAN_START_STAGE_H