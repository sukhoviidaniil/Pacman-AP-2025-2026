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

#include "infra/internal/Const_Score.h"
#include "infra/menu/MenuView.h"
#include "model/ModelView.h"

namespace view {
    struct ViewContext {
        const bool redrawing;
        const std::optional<std::reference_wrapper<const infra::menu::MenuView>> menu;
        const std::optional<std::reference_wrapper<const infra::Const_Score>> score;
        const std::optional<std::reference_wrapper<const infra::Const_ScoreBord>> score_bord;
        const std::optional<std::reference_wrapper<const model::ui::ModelView>> model;
        explicit ViewContext(
            const bool redraw,
            const infra::menu::MenuView* mn = nullptr,
            const infra::Const_Score* s = nullptr,
            const infra::Const_ScoreBord* sb = nullptr,
            const model::ui::ModelView* m = nullptr
         )
         :  redrawing(redraw),
            menu(mn ? std::optional(std::cref(*mn)) : std::nullopt),
            score(s ? std::optional(std::cref(*s)) : std::nullopt),
            score_bord(sb ? std::optional(std::cref(*sb)) : std::nullopt),
            model(m ? std::optional(std::cref(*m)) : std::nullopt)
        {}
    };
}

#endif //PACMAN_VIEWCONTEXT_H