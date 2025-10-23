/***************************************************************
 * Project:       Pacman
 * File:          DebugConstants.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-10-23
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
#ifndef PACMAN_DEBUGCONSTANTS_H
#define PACMAN_DEBUGCONSTANTS_H
#include <string>

#include "Constant.h"
namespace Constants {
    class DebugConstants:Constant {
    public:
        void loadFromFile(const std::string& path);
    };
}

#endif //PACMAN_DEBUGCONSTANTS_H