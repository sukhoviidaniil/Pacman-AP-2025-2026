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


        // ===== Read-only accessors =====
        [[nodiscard]] const std::vector<std::shared_ptr<entity::Coin>>& coins() const {
            return model_.coins_;
        }
        [[nodiscard]] const std::vector<std::shared_ptr<entity::PowerPellet>>& power_pellets() const {
            return model_.power_pellets_;
        }

        [[nodiscard]] const std::vector<std::shared_ptr<entity::Ghost>>& ghosts() const {
            return model_.ghosts_;
        }

        [[nodiscard]] const infra::Status& ghosts_status() const {
            return model_.ghosts_status;
        }

        [[nodiscard]] const std::shared_ptr<entity::Pacman>& pacman() const {
            return model_.pacman_;
        }

        [[nodiscard]] const infra::Status& pacman_status() const {
            return model_.pacman_status;
        }

        [[nodiscard]] const Tile_Grid& grid() const {
            return *model_.grid_;
        }

    private:
        const Model& model_;
    };
}

#endif //PACMAN_MODELVIEW_H