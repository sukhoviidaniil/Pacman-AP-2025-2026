/***************************************************************
 * Project:       Pacman
 * File:          Stage_Manager.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-28
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

#include <utility>

#include "core/Stage_Manager.h"

#include "infra/event/events/game.h"


namespace core  {
    /*
    Stage_Manager::Stage_Manager(const std::shared_ptr<Game_Model> &game_model) : game_model_(game_model) {

        std::shared_ptr<Stage> start_stage = ;// TODO add start stage
        push_stage(start_stage);
    }

    Stage_Manager::~Stage_Manager() = default;

    void Stage_Manager::handle_PacmanDied() {
        if (current_stages_.empty()) return;
        const auto old_stage = get_top();

        // TODO Use Factory to define Stage
        int score = dynamic_cast<PlayingStage*>(old_stage.get())->score;
        auto new_stage = std::make_shared<DeathStage>(score);

        current_stages_.pop();
        current_stages_.push(new_stage);
    }

    void Stage_Manager::add_Stage_Info(const std::shared_ptr<Stage_Info>& info) {
        const std::string name = info->name;
        auto it = stages_info.find(name);
        if (it == stages_info.end()) {
            stages_info[name] = info;
            return;
        }
        throw std::runtime_error("Stage already exists");
    }
    */

    Stage_Manager::~Stage_Manager() = default;

    Stage_Manager::Stage_Manager() = default;

    void Stage_Manager::set_stage_factory(std::unique_ptr<core::Stage_Factory> stage_factory) {
        stage_factory_ = std::move(stage_factory);
    }

    void Stage_Manager::track_global(const std::shared_ptr<infra::event::Event_Bus> &bus) {
        track(
            bus->subscribe<infra::event::game::Request_StartStage>(
                [this](const infra::event::game::Request_StartStage&) {
                    current_stages_ = {};
                    push_stage(stage_factory_->make_Start_Stage());
                }
            )
        );
        track(
            bus->subscribe<infra::event::game::Request_NewLevelStage>(
                [this](const infra::event::game::Request_NewLevelStage&) {
                    pop_stage();
                    push_stage(stage_factory_->make_new_Game_Stage());
                }
            )
        );
        track(
            bus->subscribe<infra::event::game::Request_NextLevelStage>(
                [this](const infra::event::game::Request_NextLevelStage&) {
                    pop_stage();
                    push_stage(stage_factory_->make_next_Game_Stage());
                }
            )
        );
        track(
            bus->subscribe<infra::event::game::Request_EnterPause>(
                [this](const infra::event::game::Request_EnterPause&) {
                    push_stage(stage_factory_->make_pause_stage());
                }
            )
        );
        track(
            bus->subscribe<infra::event::game::Request_ExitPause>(
                [this](const infra::event::game::Request_ExitPause&) {
                    pop_stage();
                }
            )
        );
        track(
            bus->subscribe<infra::event::game::Request_DeathStage>(
                [this](const infra::event::game::Request_DeathStage&) {
                    pop_stage();
                    push_stage(stage_factory_->make_death_stage());
                }
            )
        );
    }

    void Stage_Manager::pop_stage() {
        if (current_stages_.empty()) return;
        current_stages_.pop();
    }

    void Stage_Manager::push_stage(const std::shared_ptr<core::stg::Stage> &stage) {
        current_stages_.push(stage);
    }

    std::shared_ptr<core::stg::Stage> Stage_Manager::get_top() {
        if (current_stages_.empty()) return nullptr;
        return current_stages_.top();
    }
}
