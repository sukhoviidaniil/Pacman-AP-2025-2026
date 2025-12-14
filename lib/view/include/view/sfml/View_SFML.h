/***************************************************************
 * Project:       Pacman
 * File:          View_SFML.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-13
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
#ifndef PACMAN_VIEW_SFML_H
#define PACMAN_VIEW_SFML_H
#include <map>
#include <memory>
#include <string>


#include "SFML/Graphics.hpp"


namespace view {
    class View_SFML {
        // key - name of file
        std::map<
            std::string,
            sf::Texture
        > textures_;

        // key - construct name
        std::map<
            std::string,
            std::shared_ptr<sf::Sprite>
        > sprites_;

        // key - entity name
        std::map<
            std::string,
            std::shared_ptr<Sprite_Group>
        > sprite_groups_;

    };
}

#endif //PACMAN_VIEW_SFML_H