/***************************************************************
 * Project:       Pacman
 * File:          GhostRole.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-28
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
#ifndef PACMAN_GHOSTROLE_H
#define PACMAN_GHOSTROLE_H
#include <string>

namespace model::ai {

    /**
     * @brief Enum representing the different ghost roles in the game.
     */
    enum class GhostRole {
        Blinky,
        Pinky,
        Inky,
        Clyde
    };

    /**
     * @brief Converts a GhostRole to its string representation.
     *
     * @param role The GhostRole value
     * @return Name of the ghost as a string
     */
    inline std::string role_name(const GhostRole role) {
        switch (role) {
            case GhostRole::Blinky : return "Blinky";
            case GhostRole::Pinky : return "Pinky";
            case GhostRole::Inky : return "Inky";
            case GhostRole::Clyde : return "Clyde";
            default: return "None";
        }
    }
}

#endif //PACMAN_GHOSTROLE_H