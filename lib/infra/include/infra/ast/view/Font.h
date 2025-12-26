/***************************************************************
 * Project:       Pacman
 * File:          Font.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-26
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
#ifndef PACMAN_AST_FONT_H
#define PACMAN_AST_FONT_H
#include "ViewNode.h"

namespace infra::ast {
    struct Font : Node{
        std::string font;
        std::string file;
    };
}
#endif //PACMAN_AST_FONT_H