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
#include "view/presentation/external/Color.h"

namespace view::ui {
    struct RI_Label : RenderItem {
        /**
         * @brief Any text
         */
        std::string text;
        Color color;

    };
}
#endif //PACMAN_AST_RI_TEXT_H