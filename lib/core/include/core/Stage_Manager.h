/***************************************************************
 * Project:       Pacman
 * File:          Stage_Manager.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-26
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
#ifndef PACMAN_STAGE_MANAGER_H
#define PACMAN_STAGE_MANAGER_H

#include "core/Stage.h"
#include <unordered_map>
#include <memory>
#include <stack>

namespace Core {
    class Stage_Manager {
        std::unordered_map<
            std::string,
            std::shared_ptr<Stage>
        > stages_;
        std::stack<std::shared_ptr<Stage>> current_stages_;
        public:

        Stage_Manager();
        ~Stage_Manager();
        void add_Stage(const std::string &name, const std::shared_ptr<Stage> &stage);

        void pop_stage();
        void push_stage(const std::string &name);

        std::shared_ptr<Stage> get_current_stage();
    };
}

#endif //PACMAN_STAGE_MANAGER_H