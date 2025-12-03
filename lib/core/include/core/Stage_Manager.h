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
    class File_Reader;
    class Stage_Manager {
        std::shared_ptr<const File_Reader> fr_;
        std::unordered_map<
            std::string,
            std::unique_ptr<Stage_Info>
        > stages_info;
        std::stack<std::shared_ptr<Stage>> current_stages_;
        public:

        explicit Stage_Manager(const std::shared_ptr<const File_Reader>& fr);
        ~Stage_Manager();

        void add_Stage_Info(std::unique_ptr<Stage_Info> info);

        void pop_stage();
        void push_stage(const std::string &name);

        std::shared_ptr<Stage> get_current_stage();
    };
}

#endif //PACMAN_STAGE_MANAGER_H