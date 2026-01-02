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


#include "collision/Collision_Control.h"
#include "entity/Coin.h"
#include "entity/Ghost.h"
#include "infra/ast/model/Model.h"

#include "infra/event/Event_Store.h"


#include "entity/Pacman.h"
#include "entity/PowerPellet.h"

#include "infra/internal/Score.h"


namespace model {
    class Model {
        public:

        explicit Model(
            const infra::ast::Model& m,
            const std::shared_ptr<infra::Score>& score,
            std::unique_ptr<collision::Collision_Control> cc,
            std::vector<std::shared_ptr<entity::Coin>> coins,
            std::vector<std::shared_ptr<entity::PowerPellet>> power_pellets
            );

        void add_wait();

        [[nodiscard]] bool all_coins_collected() const;

        void run(float delta);

        [[nodiscard]] std::shared_ptr<entity::Pacman> get_pacman() const;
        [[nodiscard]] infra::Status pacman_status() const;


        std::vector<std::shared_ptr<entity::Coin>> coins_;
        std::vector<std::shared_ptr<entity::PowerPellet>> power_pellets_;
        std::vector<std::shared_ptr<entity::Ghost>> ghosts_;
        std::shared_ptr<entity::Pacman> pacman_;
        TileGrid grid_;
        infra::event::Event_Store event_store_;
    protected:
        infra::Status pacman_status_ = infra::Status::Alive;



        [[nodiscard]] std::vector<std::shared_ptr<entity::Coin>> get_coins_near(const TilePos& pos) const;
        [[nodiscard]] std::vector<std::shared_ptr<entity::PowerPellet>> get_power_pellets_near(const TilePos& pos) const;
        [[nodiscard]] std::vector<std::shared_ptr<entity::Ghost>> get_ghosts_near(const TilePos& pos) const;


    private:

        void remove_coin(const std::shared_ptr<entity::Coin>& coin_to_remove);
        void remove_power_pellet(const std::shared_ptr<entity::PowerPellet>& pp_to_remove);

        void process_tile(const infra::ast::Model &m, const unsigned int &level,
                            const infra::ast::Tile &in_cell,
                            const infra::math::Point2 &position);

        std::vector<entity::Ghost> make_Ghosts(const std::string &name, float hb_size,
                                               const infra::math::Point2 &position, const unsigned int &level, infra::ast::GhostInfo info);

        bool process_tile_without_consumables(const infra::ast::Model &m, const unsigned int &level,
                                              const infra::ast::Tile &in_cell,
                                              const infra::math::Point2 &position);

        std::vector<std::shared_ptr<entity::Ghost>> blinkys_;
        std::unique_ptr<collision::Collision_Control> collision_control_;
        std::shared_ptr<infra::Score> score_;

        float start_wait_ = 1;
        float death_wait_ = 2;
        bool powered_ = false;
        float buff_wait_ = 1;
    };
}

#endif //PACMAN_MODEL_H