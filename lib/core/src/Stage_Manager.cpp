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

#include "../include/core/Stage_Manager.h"


namespace control  {
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

    void Stage_Manager::pop_stage() {
        if (current_stages_.empty()) return;
        current_stages_.pop();
    }

    void Stage_Manager::push_stage(const std::shared_ptr<model::Stage> &stage) {
        current_stages_.push(stage);
        un_track_all();
        track(stage);
    }

    std::shared_ptr<model::Stage> Stage_Manager::get_top() {
        return current_stages_.top();
    }
}
