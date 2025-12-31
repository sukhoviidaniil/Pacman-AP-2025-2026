/***************************************************************
 * Project:       Pacman
 * File:          Pause_Stage.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-31
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
#ifndef PACMAN_PAUSE_STAGE_H
#define PACMAN_PAUSE_STAGE_H
#include "core/Stage.h"

namespace core::stg {
    class Pause_Stage : public stg::Stage{
    public:
        ~Pause_Stage() override;
        Pause_Stage(
            const std::shared_ptr<infra::event::Event_Bus> &global_eventbus,
            infra::Const_Score score
        );
        void run(float tick) override;
        [[nodiscard]] view::ui::RenderFrame get_RenderFrame(const infra::math::Vector2& screen_size, bool redraw) const override;
    private:
        infra::Const_Score score_;
        std::shared_ptr<infra::menu::Menu> menu_;
    };
}

#endif //PACMAN_PAUSE_STAGE_H