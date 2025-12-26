/***************************************************************
 * Project:       Pacman
 * File:          RI_Label.h
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
#ifndef PACMAN_AST_RI_TEXT_H
#define PACMAN_AST_RI_TEXT_H
#include "RenderItem.h"
#include "infra/presentation/external/Color.h"

namespace view::ui {
    struct RI_Label : RenderItem {
        /**
         * @brief Any text
         */
        std::string text;
        /**
         * @brief Any Font of text
         */
        std::string font;
        infra::ui::Color color;
        int size = 0;

        void accept(RenderVisitor &v) const override {
            v.visit(*this);
        }
    };
}
#endif //PACMAN_AST_RI_TEXT_H