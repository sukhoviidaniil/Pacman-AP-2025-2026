/***************************************************************
 * Project:       Pacman
 * File:          Map.h
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
#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H
#include "view/presentation/layout_engine/UIElement.h"

namespace view::ui {
    class Map : public UIElement {
    public:
        infra::math::Point2 world_to_ui(const infra::math::Point2& p) const;
    };
}

#endif //PACMAN_MAP_H