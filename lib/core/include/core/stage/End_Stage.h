/***************************************************************
 * Project:       Pacman
 * File:          End_Stage.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-04
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
#ifndef PACMAN_END_STAGE_H
#define PACMAN_END_STAGE_H
#include "core/Stage.h"

namespace core::stg {

    class End_Stage : public Stage {
    public:

        End_Stage(const std::shared_ptr<infra::event::Event_Bus> &global_eventbus, infra::Const_Score s,
                  infra::Const_ScoreBord sb);

        void run(float tick) override;

        [[nodiscard]] view::ui::RenderFrame get_RenderFrame(const infra::math::Vector2& screen_size, bool redraw) const override;

    private:
        std::shared_ptr<infra::menu::Menu> menu_;
        infra::Const_Score s_;
        infra::Const_ScoreBord sb_;
    };
}

#endif //PACMAN_END_STAGE_H