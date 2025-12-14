/***************************************************************
 * Project:       Pacman
 * File:          Status_Info.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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
#ifndef PACMAN_STATUS_INFO_H
#define PACMAN_STATUS_INFO_H

#include "core/info/Expression_Info.h"
#include "core/info/rec_Info.h"

namespace core {
    struct Status_Info {
        std::vector<Expression_Info> facial_expressions;
        int number_of_expressions_per_direction = 1;
        rec_Info recLeft;
        rec_Info recTop;

        Status_Info() = default;
        // explicit Status_Info (const nlohmann::json& j);
    };
}

#endif //PACMAN_STATUS_INFO_H