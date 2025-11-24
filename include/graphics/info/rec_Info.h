/***************************************************************
 * Project:       Pacman
 * File:          rec_Info.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-20
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
#ifndef PACMAN_REC_INFO_H
#define PACMAN_REC_INFO_H

#include "func/json.hpp"

namespace Graphics::Info {
    struct rec_Info {
        unsigned int base = 0;
        unsigned int increase = 0;
    };
    inline void from_json(const nlohmann::json& j, rec_Info& s) {
        s.base = j.value<unsigned int>("base", 0);
        s.increase = j.value<unsigned int>("increase", 0);
    }
}

#endif //PACMAN_REC_INFO_H