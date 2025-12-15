/***************************************************************
 * Project:       Pacman
 * File:          Application.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-02
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
#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <string>

#include "AST_Base.h"

namespace infra::ast {
    struct Application : Node{
        int window_width = -1;
        int window_height = -1;
        std::string view_type = "None";
        std::string view_conf = "wrong_path_no_conf.json";
        std::string stage_mng = "wrong_path_no_conf.json";
    };
}

#endif //PACMAN_APPLICATION_H