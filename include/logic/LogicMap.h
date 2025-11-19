/***************************************************************
 * Project:       Pacman
 * File:          LogicMap.h
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
#ifndef PACMAN_LOGICMAP_H
#define PACMAN_LOGICMAP_H
#include <vector>

namespace Logic {
    class LogicMap {
        unsigned int height, width;
        public:
        std::vector<std::vector<int>> map;
        LogicMap();
        explicit LogicMap(unsigned int height, unsigned int width);
        explicit LogicMap(std::vector<std::vector<int> > t_map);
        void set_height(unsigned int t_height);
        void set_width(unsigned int t_width);
        // == Comparison ==========
        [[nodiscard]] bool same_size(const LogicMap& other) const;
    };
}

#endif //PACMAN_LOGICMAP_H