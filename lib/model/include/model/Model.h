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
#include "infra/presentation/RenderFrame.h"
#include "infra/event/Event_Store.h"

#include "entity/Coin.h"
#include "entity/Pacman.h"
#include "entity/Ghost.h"
#include "infra/Score.h"

namespace model {
    class Model {
        public:

        explicit Model(const infra::ast::Model& m, const unsigned int& level);
        explicit Model(const infra::ast::Model& m, const unsigned int& level, const std::vector<std::shared_ptr<entity::Coin>>& coins);

        std::vector<std::shared_ptr<entity::Coin>> get_coins() const;
        bool all_coins_eaten() const;

        void run(float delta);

        [[nodiscard]] infra::ui::RenderFrame build_render_frame_Grid(const infra::ui::Camera &camera) const;
        [[nodiscard]] infra::ui::RenderFrame build_render_frame_Entity(const infra::ui::Camera &camera) const;


        [[nodiscard]] std::shared_ptr<entity::Pacman> get_pacman() const;
        [[nodiscard]] std::optional<infra::ui::Animation> get_animation(const std::string &name, const infra::ast::Tile& type) const;

        infra::event::Event_Store event_store_;
        private:

        void create_model(const infra::ast::Model& m, const unsigned int& level);
        void create_model(const infra::ast::Model& m, const unsigned int& level, std::vector<std::shared_ptr<entity::Coin>>);

        std::vector<std::shared_ptr<entity::Coin>> coins;
        std::vector<std::shared_ptr<entity::Ghost>> ghosts;
        std::shared_ptr<entity::Pacman> pacman;
        std::shared_ptr<Tile_Grid> grid;
        collision::World_Collision_Manager wcm_;

        std::unordered_map<
            std::string, // Entity name
            infra::ui::Animation
        > animation;
        std::unordered_map<
            infra::ast::Tile, // Type of entity
            infra::ui::Animation
        > animation_variant;
        float elapsed; // If Animation not in map
    };
}

#endif //PACMAN_MODEL_H