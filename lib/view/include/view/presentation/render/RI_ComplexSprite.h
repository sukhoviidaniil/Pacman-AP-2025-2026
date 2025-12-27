/***************************************************************
 * Project:       Pacman
 * File:          RI_ComplexSprite.h
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
#ifndef PACMAN_AST_RI_COMPLEXSPRITE_H
#define PACMAN_AST_RI_COMPLEXSPRITE_H
#include "view/presentation/render/RI_Sprite.h"
#include "../../../../../infra/include/infra/internal/Status.h"
#include "infra/math/Direction.h"

namespace view::ui {
    struct RI_ComplexSprite : RI_Sprite {
        /**
         * @brief Direction (e.g., "up", "down", "left", "right").
         */
        infra::math::Direction direction;

        /**
         * @brief Status (e.g., "idle", "walking", "attacking").
         */
        infra::Status status;

        void accept(RenderVisitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_AST_RI_COMPLEXSPRITE_H
