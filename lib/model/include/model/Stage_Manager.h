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

#include "model/Stage.h"
#include <unordered_map>
#include <memory>
#include <stack>

#include "Game_Model.h"
#include "infra/Observer.h"

namespace model {

    class Stage_Manager : public infra::Observer {

        std::shared_ptr<Game_Model> game_model_;

        std::unordered_map<
            std::string,
            std::shared_ptr<Stage>
        > stages_;

        std::unordered_map<
            std::string,
            std::shared_ptr<Stage_Info>
        > stages_info;
        std::stack<std::shared_ptr<Stage>> current_stages_;
        public:

        explicit Stage_Manager();
        ~Stage_Manager() override;

        void handle_PacmanDied();
















        void add_Stage_Info(const std::shared_ptr<Stage_Info>& info);

        void pop_stage();
        void push_stage(const std::shared_ptr<Stage> &stage);

        std::shared_ptr<Stage> get_top();
    };
}

#endif //PACMAN_STAGE_MANAGER_H