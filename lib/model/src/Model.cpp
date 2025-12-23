/***************************************************************
 * Project:       Pacman
 * File:          Model.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-18
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

#include "model/Model.h"

#include "model/collision/HitBox_Rectangle.h"
#include "model/collision/Separating_Axis_Theorem.h"

namespace model {
    Model::Model(const infra::ast::Model &m, const unsigned int& level) {
        create_model(m, level);

    }

    Model::Model(
        const infra::ast::Model &m, const unsigned int &level,
        const std::vector<std::shared_ptr<entity::Coin>> &coins
        ) {
        create_model(m, level, coins);
    }

    std::vector<std::shared_ptr<entity::Coin>> Model::get_coins() const {

    }

    bool Model::all_coins_eaten() const {
        return coins.empty();
    }


    void Model::run(const float delta) {
        elapsed += delta;
        for (auto& a : animation) {
            a.second.elapsed_ += delta;
        }
    }

    infra::ui::RenderFrame Model::build_render_frame_Grid(const infra::ui::Camera &camera) const {
        infra::ui::RenderFrame frame;
        frame.camera = camera;

        // Grid tiles (Background)
        if (grid) {
            const auto& tiles = grid->get_tiles();
            for (const auto & y : tiles) {
                for (const auto& tile : y) {
                    if (!tile) continue;
                    infra::ui::RenderItem tile_item;
                    tile_item.type = infra::ui::ItemType::Sprite;
                    tile_item.space = infra::ui::Space::World;
                    tile_item.rect = tile->get_rect();
                    tile_item.sprite = "tile";
                    tile_item.direction = infra::math::Direction::None;
                    frame.items.push_back(tile_item);
                }
            }
        }
        return frame;
    }


    infra::ui::RenderFrame Model::build_render_frame_Entity(const infra::ui::Camera& camera) const {
        infra::ui::RenderFrame frame;
        frame.camera = camera;

        // Pacman
        if (pacman) {
            // TODO pacman render
            infra::ui::RenderItem pac_item;
            pac_item.type = infra::ui::ItemType::ComplexSprite;
            pac_item.space = infra::ui::Space::World;
            pac_item.rect =pacman->get_rect();
            pac_item.sprite = "Blinky";
            pac_item.direction = pacman->get_direction();
            pac_item.status = pacman->status_;
            pac_item.animation = get_animation("Blinky", infra::ast::Tile::PacmanSpawn);
            frame.items.push_back(pac_item);
        }

        // Ghosts
        for (const auto& g : ghosts) {
            if (!g) continue;
            infra::ui::RenderItem ghost_item;
            ghost_item.type = infra::ui::ItemType::Sprite;
            ghost_item.space = infra::ui::Space::World;
            ghost_item.rect = g->get_rect();
            ghost_item.sprite = "Ghost";
            ghost_item.direction = g->get_direction();
            // ghost_item.status = g->status;
            ghost_item.animation = get_animation("Ghost", infra::ast::Tile::GhostSpawn);
            frame.items.push_back(ghost_item);
        }

        // Coins
        for (const auto& c : coins) {
            if (!c) continue;
            infra::ui::RenderItem coin_item;
            coin_item.type = infra::ui::ItemType::Sprite;
            coin_item.space = infra::ui::Space::World;
            coin_item.rect = c->get_rect();
            coin_item.sprite = "coin";
            coin_item.direction = infra::math::Direction::None;
            frame.items.push_back(coin_item);
        }

        return frame;
    }

    std::shared_ptr<entity::Pacman> Model::get_pacman() const {
        return pacman;
    }

    std::optional<infra::ui::Animation> Model::get_animation(const std::string &name, const infra::ast::Tile& type) const {
        auto it1 = animation.find(name);
        if (it1 != animation.end()) {
            // A specific animator was found.
            return it1->second;
        }
        auto it2 = animation_variant.find(type);
        if (it2 != animation_variant.end()) {
            // A common animation was found.
            return infra::ui::Animation(it2->second, elapsed);
        }
        // Animation not found
        return std::nullopt;
    }

    void Model::create_model(const infra::ast::Model &m, const unsigned int &level) {

        grid = std::make_shared<Tile_Grid>(m.grid);
        auto sat = std::make_unique<collision::Separating_Axis_Theorem>();
        wcm_ = collision::World_Collision_Manager(std::move(sat), grid);

        const std::vector<std::vector<infra::ast::Tile>>& s_grid = m.grid.grid;
        const unsigned int rows = m.grid.rows;
        const unsigned int columns = m.grid.columns;

        for (unsigned int y = 0; y < rows; ++y) {
            for (unsigned int x = 0; x < columns; ++x) {
                const infra::ast::Tile& in_cell = s_grid[y][x];
                std::shared_ptr<const entity::Tile> tile = grid->get_tile(y, x);
                if (tile == nullptr) continue;
                infra::math::Point2 position = tile->get_position();
                switch (in_cell) {
                    case infra::ast::Tile::PacmanSpawn: {
                        float size = m.pacman_spawn.size;
                        float speed = m.pacman_spawn.speed;
                        auto h = std::make_unique<collision::HitBox_Rectangle>(position, size, size, 0);
                        pacman = std::make_shared<entity::Pacman>(position, std::move(h), speed);

                        animation["Blinky"] = infra::ui::Animation(4, 1, 0);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }

    void Model::create_model(const infra::ast::Model &m, const unsigned int &level,
        std::vector<std::shared_ptr<entity::Coin>>) {
    }
}
