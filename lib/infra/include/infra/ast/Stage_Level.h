/***************************************************************
 * Project:       Pacman
 * File:          Stage_Level_Node.h
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
#ifndef PACMAN_STAGE_LEVEL_NODE_H
#define PACMAN_STAGE_LEVEL_NODE_H

#include "Stage.h"

#include <string>
#include <vector>

namespace infra::ast {
    struct Stage_Level_Node : Stage_Node {
        std::vector<std::vector<std::string>> grid;
        size_t rows;
        size_t columns;

        ~Stage_Level_Node() override = default;

        void accept(Visitor& v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_STAGE_LEVEL_NODE_H