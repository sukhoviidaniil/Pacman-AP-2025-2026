/***************************************************************
 * Project:       Pacman
 * File:          Logic_Map.h
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
    class Logic_Map {
        unsigned int height, width;
        public:
        std::vector<std::vector<int>> map;
        Logic_Map();
        explicit Logic_Map(unsigned int height, unsigned int width);
        explicit Logic_Map(std::vector<std::vector<int> > t_map);
        void set_height(unsigned int t_height);
        void set_width(unsigned int t_width);
        // == Comparison ==========
        [[nodiscard]] bool same_size(const Logic_Map& other) const;
    };
}

#endif //PACMAN_LOGICMAP_H