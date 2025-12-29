/***************************************************************
 * Project:       Pacman
 * File:          Level_Stage.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-23
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
#ifndef PACMAN_GAME_STAGE_H
#define PACMAN_GAME_STAGE_H
#include "core/Stage.h"
#include "model/Model.h"
#include "view/presentation/layout_engine/UIElement.h"
#include "view/presentation/render/RenderFrame.h"

namespace core::stg{
    class Level_Stage : public Stage {

        public:
        ~Level_Stage() override;

        Level_Stage(
            const std::shared_ptr<infra::event::Event_Bus> &global_eventbus,
            const std::shared_ptr<model::Model>& model,
            infra::Const_Score score
        );

        void run(float tick) override;

        [[nodiscard]] view::ui::RenderFrame get_RenderFrame(const infra::math::Vector2& screen_size, bool redraw) const override;
        private:

        std::shared_ptr<model::Model> model_; /// Model of this stage (Controller can have ptr)
        infra::Const_Score score_;

        float p = 3.f;
    };
}

#endif //PACMAN_GAME_STAGE_H