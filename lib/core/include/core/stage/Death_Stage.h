/***************************************************************
 * Project:       Pacman
 * File:          Death_Stage.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-03
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
#ifndef PACMAN_DEATH_STAGE_H
#define PACMAN_DEATH_STAGE_H
#include "core/Stage.h"

namespace core::stg {

    class Death_Stage : public Stage {
    public:
        Death_Stage(
            const std::shared_ptr<infra::event::Event_Bus> &global_eventbus,
            infra::Const_Score score
        );

        void run(float tick) override;

        [[nodiscard]] view::ui::RenderFrame get_RenderFrame(const infra::math::Vector2& screen_size, bool redraw) const override;

    private:
        infra::event::Event_Store event_store_;
        infra::Const_Score score_;
        float elapsed_ = 3.0;
    };
}

#endif //PACMAN_DEATH_STAGE_H