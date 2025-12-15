/***************************************************************
 * Project:       Pacman
 * File:          Manager_Stages.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-14
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
#ifndef PACMAN_MANAGER_STAGES_H
#define PACMAN_MANAGER_STAGES_H

#include "AST_Base.h"

#include <memory>
#include <vector>

namespace infra::ast {
    struct Manager_Stages : Node{
        std::vector<std::shared_ptr<Stage>> stages;
    };
}

#endif //PACMAN_MANAGER_STAGES_H