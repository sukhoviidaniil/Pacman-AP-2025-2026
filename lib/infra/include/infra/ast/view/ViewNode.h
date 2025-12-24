/***************************************************************
 * Project:       Pacman
 * File:          ViewNode.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-24
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
#ifndef PACMAN_AST_VIEWNODE_H
#define PACMAN_AST_VIEWNODE_H
#include <string>

#include "infra/ast/Node.h"

namespace infra::ast {
    struct SpriteVisitor;

    struct SpriteNode : Node {
        std::string using_texture;
        unsigned int sprits_width;
        unsigned int sprits_height;
        ~SpriteNode() override = default;
        virtual void accept(SpriteVisitor &v) const {
        }
    };
}

#endif //PACMAN_AST_VIEWNODE_H