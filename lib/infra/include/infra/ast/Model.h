/***************************************************************
 * Project:       Pacman
 * File:          Model.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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
#ifndef PACMAN_MODEL_H
#define PACMAN_MODEL_H
#include <string>
#include <vector>


namespace infra::ast {
    struct Model {
        unsigned int rows;
        unsigned int columns;
        std::vector<std::vector<std::string>> grid;
    };
}
#endif //PACMAN_MODEL_H