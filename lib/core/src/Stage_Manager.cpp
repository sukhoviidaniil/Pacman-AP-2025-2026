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

#include "core/Stage_Manager.h"

namespace Core {
    Stage_Manager::Stage_Manager() = default;

    Stage_Manager::~Stage_Manager() = default;

    void Stage_Manager::add_Stage(const std::string &name, const std::shared_ptr<Stage> &stage) {
        if (stage == nullptr) return;
        stages_[name] = stage;
    }

    void Stage_Manager::pop_stage() {
        if (stages_.empty()) return;
        current_stages_.pop();
    }

    void Stage_Manager::push_stage(const std::string &name) {
        auto it = stages_.find(name);
        if (it == stages_.end()) return;
        current_stages_.push(it->second);
    }

    std::shared_ptr<Stage> Stage_Manager::get_current_stage() {
        return current_stages_.top();
    }
}
