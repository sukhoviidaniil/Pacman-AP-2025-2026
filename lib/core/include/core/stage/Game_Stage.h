/***************************************************************
 * Project:       Pacman
 * File:          Game_Stage.h
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
#include "../../../../infra/include/infra/internal/Score.h"
#include "model/Model.h"
#include "view/presentation/layout_engine/UIElement.h"
#include "view/presentation/render/RenderFrame.h"

namespace core{
    class Game_Stage : public Stage {

        public:
        ~Game_Stage() override;

        Game_Stage(
            const std::shared_ptr<infra::event::Event_Bus> &global_eventbus,
            const std::shared_ptr<model::Model>& model
        );

        void run(float tick) override;

        [[nodiscard]] view::ui::RenderFrame get_RenderFrame(const infra::math::Vector2& screen_size, bool redraw) const override;
        private:

        std::shared_ptr<model::Model> model_; /// Model of this stage (Controller can have ptr)
        std::shared_ptr<infra::Score> score_; /// Model MUST have this || Stage can have this for UI
    };
}

#endif //PACMAN_GAME_STAGE_H