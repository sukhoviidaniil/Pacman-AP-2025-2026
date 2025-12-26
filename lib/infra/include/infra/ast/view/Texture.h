/***************************************************************
 * Project:       Pacman
 * File:          Texture.h
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
#ifndef PACMAN_AST_TEXTURE_H
#define PACMAN_AST_TEXTURE_H
#include <string>

#include "infra/ast/Node.h"

namespace infra::ast {
    struct Texture : Node{
        std::string name;
        std::string file;
    };
}

#endif //PACMAN_AST_TEXTURE_H