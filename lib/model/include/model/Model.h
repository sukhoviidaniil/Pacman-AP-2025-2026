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


#include "ai/internal/GhostRole.h"
#include "collision/Collision_Control.h"
#include "entity/Coin.h"
#include "entity/Ghost.h"
#include "infra/ast/model/Model.h"

#include "infra/event/Event_Store.h"


#include "entity/Pacman.h"
#include "entity/PowerPellet.h"

#include "infra/internal/Score.h"


namespace model {

    /**
     * @brief Core game model.
     *
     * Acts as a central coordinator for game entities, grid state,
     * collision handling, scoring, and update logic.
     *
     * The Model owns and updates Pac-Man, ghosts, consumables,
     * and propagates game events.
     */
    class Model {
        public:

        /**
         * @brief Constructs the game model from an AST description.
         *
         * @param m Parsed model definition (e.g. level layout).
         * @param score Shared score object.
         * @param cc Collision control system.
         * @param coins Initial coin entities.
         * @param power_pellets Initial power pellet entities.
         */
        explicit Model(
            const infra::ast::Model& m,
            const std::shared_ptr<infra::Score>& score,
            std::unique_ptr<collision::Collision_Control> cc,
            std::vector<std::shared_ptr<entity::Coin>> coins,
            std::vector<std::shared_ptr<entity::PowerPellet>> power_pellets
            );

        /**
         * @brief Adds a waiting period to the game state.
         *
         * @todo Clarify when and why this wait is triggered.
         */
        void add_wait();

        /**
         * @brief Checks whether all coins have been collected.
         *
         * @return True if no collectible coins remain.
         */
        [[nodiscard]] bool all_coins_collected() const;

        /**
         * @brief Advances the game simulation.
         *
         * Updates entities, processes collisions, and
         * advances internal timers.
         *
         * @param delta Time elapsed since the last update.
         */
        void run(float delta);

        /**
         * @brief Returns the Pac-Man entity.
         */
        [[nodiscard]] std::shared_ptr<entity::Pacman> get_pacman() const;

        /**
         * @brief Returns the current status of Pac-Man.
         */
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

        void make_Ghosts(const ai::GhostRole &role,
                                               float hb_size, const infra::math::Point2 &position, const unsigned int &level, const infra::ast::GhostInfo& info);

        bool process_tile_without_consumables(const infra::ast::Model &m, const unsigned int &level,
                                              const infra::ast::Tile &in_cell,
                                              const infra::math::Point2 &position);

        std::vector<std::shared_ptr<entity::Ghost>> blinkys_;
        std::unique_ptr<collision::Collision_Control> collision_control_;
        std::shared_ptr<infra::Score> score_;

        float start_wait_ = 1;
        float death_wait_ = 2;
    };
}

#endif //PACMAN_MODEL_H