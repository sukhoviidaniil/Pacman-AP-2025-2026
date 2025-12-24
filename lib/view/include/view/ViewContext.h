/***************************************************************
 * Project:       Pacman
 * File:          ViewContext.h
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
#ifndef PACMAN_VIEWCONTEXT_H
#define PACMAN_VIEWCONTEXT_H
#include "model/ModelView.h"

namespace view {
    struct ViewContext {
        const bool redrawing;
        const model::ui::ModelView& model;
        explicit ViewContext(const model::ui::ModelView& m, const bool redraw = false)
            :  redrawing(redraw), model(m) {}
    };
}

#endif //PACMAN_VIEWCONTEXT_H