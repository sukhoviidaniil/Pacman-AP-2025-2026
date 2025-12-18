/***************************************************************
 * Project:       Pacman
 * File:          View.h
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
#ifndef PACMAN_AST_VIEW_H
#define PACMAN_AST_VIEW_H

#include <optional>
#include <string>
#include <vector>

#include "Camera.h"
#include "Sprite.h"
#include "Complex_Sprite.h"

namespace infra::ast {
    struct View : View_Node{
        std::string type = "None";
        unsigned int window_width = 0;
        unsigned int window_height = 0;
        std::vector<std::string> textures;
        std::vector<Sprite> sprites;
        std::vector<Complex_Sprite> complex_sprites;

        std::optional<Camera> ui_camera;
        std::optional<Camera> model_camera;

    };
}

#endif //PACMAN_AST_VIEW_H