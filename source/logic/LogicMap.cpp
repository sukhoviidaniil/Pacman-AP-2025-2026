/***************************************************************
 * Project:       Pacman
 * File:          LogicMap.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-08
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
#include "logic/LogicMap.h"

#include <stdexcept>
#include <utility>

namespace Logic {
    LogicMap::LogicMap() {
        height = 1;
        width = 1;
    }

    LogicMap::LogicMap(const unsigned int height, const unsigned int width) : height(height), width(width) {

    }

    LogicMap::LogicMap(std::vector<std::vector<int>> t_map) {
        this->map = std::move(t_map);
        this->height = map.size();
        unsigned int t_width = 0;
        for (unsigned int i = 0; i < map.size(); i++) {
            if (t_width == 0) {
                t_width = map[i].size();
            }
            if (t_width != map[i].size()) {
                throw std::invalid_argument("LogicMap size mismatch");
            }
        }
        this->width = t_width;
    }

    void LogicMap::set_height(unsigned int t_height) {
        this->height = t_height;
    }

    void LogicMap::set_width(unsigned int t_width) {
        this->width = t_width;
    }

    bool LogicMap::same_size(const LogicMap &other) const {
        return height == other.height && width == other.width;
    }
}
