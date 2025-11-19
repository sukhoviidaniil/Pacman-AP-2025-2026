/***************************************************************
 * Project:       Pacman
 * File:          func_get_json_data.h
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
#ifndef PACMAN_FUNC_GET_JSON_DATA_H
#define PACMAN_FUNC_GET_JSON_DATA_H
#include "func_open_file.h"
#include "json.hpp"

inline nlohmann::json get_json_data(const std::string &filename) {
    std::ifstream file = open_file(filename);
    nlohmann::json data;
    file >> data;
    file.close();
    return data;
}

#endif //PACMAN_FUNC_GET_JSON_DATA_H
