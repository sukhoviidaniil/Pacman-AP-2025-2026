/***************************************************************
 * Project:       Pacman
 * File:          RI_Rectangle.h
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
#ifndef PACMAN_AST_RI_RECTANGLE_H
#define PACMAN_AST_RI_RECTANGLE_H
#include "RenderItem.h"
#include "infra/presentation/external/Color.h"

namespace view::ui {
    struct RI_Rectangle : RenderItem {
        int border_width = 0;
        infra::ui::Color border_color{};
        infra::ui::Color color{};
        void accept(RenderVisitor &v) const override {
            v.visit(*this);
        }
    };
}

#endif //PACMAN_AST_RI_RECTANGLE_H
