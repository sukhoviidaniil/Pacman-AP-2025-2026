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

#include "core/File_Reader.h"

namespace Core {

    Stage_Manager::Stage_Manager(const std::shared_ptr<const File_Reader> &fr) : fr_(fr) {
    }

    Stage_Manager::~Stage_Manager() = default;

    void Stage_Manager::add_Stage_Info(const std::shared_ptr<Stage_Info>& info) {
        const std::string name = info->name;
        auto it = stages_info.find(name);
        if (it == stages_info.end()) {
            stages_info[name] = info;
            return;
        }
        throw std::runtime_error("Stage already exists");
    }

    void Stage_Manager::pop_stage() {
        if (current_stages_.empty()) return;
        current_stages_.pop();
    }

    void Stage_Manager::push_stage(const std::string &name) {
        auto it = stages_info.find(name);
        if (it == stages_info.end()) return;
        std::string filename = it->second->configuration;
        current_stages_.push(fr_->load_Stage(filename));
    }

    std::shared_ptr<Stage> Stage_Manager::get_current_stage() {
        return current_stages_.top();
    }
}
