/***************************************************************
 * Project:       Pacman
 * File:          ModelView.h
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
#ifndef PACMAN_MODELVIEW_H
#define PACMAN_MODELVIEW_H
#include "model/Model.h"

namespace model::ui {

    class ModelView {
    public:
        explicit ModelView(const model::Model& m) : model_(m) {}

        // ===== High-level state =====
        bool all_coins_eaten() const {
            return model_.all_coins_eaten();
        }

        // ===== Read-only accessors =====
        const std::vector<std::shared_ptr<entity::Coin>>& coins() const {
            return model_.coins;
        }

        const std::vector<std::shared_ptr<entity::Ghost>>& ghosts() const {
            return model_.ghosts;
        }

        const std::shared_ptr<entity::Pacman>& pacman() const {
            return model_.pacman;
        }

        const Tile_Grid& grid() const {
            return *model_.grid;
        }

        // ===== Events (read-only) =====
        const infra::event::Event_Store& events() const {
            return model_.event_store_;
        }

    private:
        const Model& model_;
    };
}

/*
*math::Point2 world_to_ui(
const math::Point2& p,
const ViewTransform& t
) {
return {
t.ui.p.x + (p.x - t.world.p.x) * t.ui.v.x / t.world.v.x,
t.ui.p.y + (p.y - t.world.p.y) * t.ui.v.y / t.world.v.y
};
}*/

#endif //PACMAN_MODELVIEW_H