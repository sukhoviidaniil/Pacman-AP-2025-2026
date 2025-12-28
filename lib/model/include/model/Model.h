/***************************************************************
 * Project:       Pacman
 * File:          Model.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-16
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
#ifndef PACMAN_MODEL_H
#define PACMAN_MODEL_H
#include <future>

#include "infra/ast/model/Model.h"

#include "infra/event/Event_Store.h"

#include "entity/Coin.h"
#include "entity/Pacman.h"
#include "entity/Ghost.h"
#include "entity/PowerPellet.h"


namespace model {
    class Model {
        public:

        explicit Model(const infra::ast::Model& m, const unsigned int& level);

        Model(const infra::ast::Model &m, const unsigned int &level, std::vector<std::shared_ptr<entity::Coin>> coins);

        [[nodiscard]] bool all_coins_eaten() const;

        void run(float delta) const;

        [[nodiscard]] std::shared_ptr<entity::Pacman> get_pacman() const;



        infra::Status pacman_status = infra::Status::Alive;
        infra::Status ghosts_status = infra::Status::Alive;
        infra::event::Event_Store event_store_;
        std::vector<std::shared_ptr<entity::Coin>> coins_;
        std::vector<std::shared_ptr<entity::PowerPellet>> power_pellets_;
        std::vector<std::shared_ptr<entity::Ghost>> ghosts_;
        std::shared_ptr<entity::Pacman> pacman_;
        std::shared_ptr<Tile_Grid> grid_;
        private:

        collision::World_Collision_Manager wcm_;

        bool process_tile(const infra::ast::Model &m, const unsigned int &level,
                            const infra::ast::Tile &in_cell,
                            const infra::math::Point2 &position);

        void process_tile_without_coins(const infra::ast::Model &m, const unsigned int &level,
                                        const infra::ast::Tile &in_cell,
                                        const infra::math::Point2 &position);
    };
}

#endif //PACMAN_MODEL_H