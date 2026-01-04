/***************************************************************
 * Project:       Pacman
 * File:          SpritsGroup.h
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
#ifndef PACMAN_SPRITEGROUP_H
#define PACMAN_SPRITEGROUP_H

#include <unordered_map>
#include "infra/internal/Status.h"
#include "infra/ast/view/internal/SpriteStatus.h"
#include "infra/ast/view/ViewNode.h"

namespace infra::ast {
    /**
     * @brief Represents a complex sprite with multiple status-based groups.
     *
     * Inherits from SpriteNode and organizes sprites into groups
     * keyed by Status. Supports the visitor pattern.
     */
    struct ComplexSprite : SpriteNode {
        std::vector<std::string> groups_names; ///< Names of sprite groups
        std::unordered_map<
            Status,
            SpriteStatus
        > groups_; ///< Mapping from status to sprite data

        /**
         * @brief Accepts a SpriteVisitor to process this complex sprite.
         */
        void accept(SpriteVisitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_SPRITEGROUP_H