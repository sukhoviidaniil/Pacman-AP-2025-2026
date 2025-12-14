/***************************************************************
 * Project:       Pacman
 * File:          View.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-06
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
#ifndef PACMAN_VIEW_H
#define PACMAN_VIEW_H



#include "SFML/graphics/RenderWindow.hpp"

#include <memory>
#include <string>

namespace view {
    class View {
    protected:
        std::string name_ = "None";
    public:
        View();
        explicit View(std::string  name);
        virtual ~View();

    };
}

#endif //PACMAN_VIEW_H