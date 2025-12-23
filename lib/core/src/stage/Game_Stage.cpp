/***************************************************************
 * Project:       Pacman
 * File:          Game_Stage.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-24
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

#include "core/stage/Game_Stage.h"




namespace core {
    Game_Stage::~Game_Stage() = default;

    Game_Stage::Game_Stage(
        const std::shared_ptr<infra::event::Event_Bus> &eventbus,
        const std::shared_ptr<model::Model> &model) :
    Stage(eventbus), model_(model){
    }

    void Game_Stage::run(float tick) {

    }

    infra::ui::RenderFrameGraph Game_Stage::get_Scene_Graph() const {
        infra::ui::RenderFrameGraph g;
        const infra::ui::Camera camera{
            .viewport_size = {600, 400},
            .position = {0,0},
            .zoom = 1
        };

        g.redraw = true;
        g.constant_frames.emplace_back(model_->build_render_frame_Grid(camera));
        g.temp_frames.emplace_back(model_->build_render_frame_Entity(camera));
        return g;
    }
}
