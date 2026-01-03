/***************************************************************
 * Project:       Pacman
 * File:          Map.cpp
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

#include "view/presentation/layout_engine/Map.h"

#include <iostream>

#include "infra/diagnostics/Logger.h"
#include "infra/diagnostics/LogScope.h"
#include "view/presentation/render/RI_ComplexSprite.h"
#include "view/presentation/render/RI_Rectangle.h"
namespace view::ui {
    void Map::layout(const infra::ui::Rect r){
        result.rect = r;  // completely fill in the parent
        for (auto& child : children) {
            // if there are nested ones, we also take up all available space
            child->layout({r.x + padding.x, r.y + padding.y,
                           r.width - padding.x*2, r.height - padding.y*2});
        }
    }

    infra::math::Vector2 Map::measure(const infra::math::Vector2& available){
        return available;
    }

    infra::math::Point2 world_to_ui(const infra::math::Point2& top_left, const infra::math::Vector2& offset, const float scale) {
        return {
            offset.x + top_left.x * scale,
            offset.y + top_left.y * scale
        };
    }


    void Map::append_render_items(RenderFrame &frame, const ViewContext &ctx) const {

        if (!ctx.model.has_value()) {
            return;
        }
        const model::ui::ModelView& model = ctx.model.value();

        auto r = std::make_unique<view::ui::RI_Rectangle>();
        r->color = infra::ui::Color(100,100,100);

        r->rect = result.rect;

        frame.constant_items.push_back(std::move(r));

        const model::TileGrid &grid = model.grid();
        const float ts = grid.tile_size();

        // Map size in world coordinates (taking into account the full size of the tiles)
        const float width  = grid.width();
        const float height = grid.height();
        infra::ui::Rect world_bounds{ 0.f, 0.f, width, height};


        // Scaling and centering the map (letterbox)
        const infra::ui::Rect& ui = result.rect;
        const float scale = std::min(
            ui.width / world_bounds.width,
            ui.height / world_bounds.height
            );

        const float map_width = world_bounds.width  * scale;
        const float map_height = world_bounds.height * scale;

        const infra::math::Vector2 offset = {
            ui.x + (ui.width  - map_width) * 0.5f,
            ui.y + (ui.height - map_height) * 0.5f
        };

        if (ctx.redrawing) {
            const float scale_tile_size = ts * scale;
            const float half_tile_size = ts * 0.5f;

            for (size_t y = 0; y < grid.rows(); ++y) {
                for (size_t x = 0; x < grid.columns(); ++x) {
                    auto pos = model::TilePos(y, x);
                    auto center = grid.get_center(pos);
                    auto tile = grid.get_tile(pos);


                    // Position conversion: tile center -> top left
                    infra::math::Point2 top_left{
                        center.x - half_tile_size,
                        center.y - half_tile_size
                    };


                    // Convert to UI coordinates
                    const infra::math::Point2 ui_pos = world_to_ui(top_left, offset, scale);

                    auto rectangle = std::make_unique<view::ui::RI_Rectangle>();

                    switch (tile) {
                        case model::Tile::Wall: {
                            rectangle->color = infra::ui::Color(0,0,255);
                            break;
                        }
                        case model::Tile::Barrier: {
                            rectangle->color = infra::ui::Color(0,255,255);
                            break;
                        }
                        default: {
                            rectangle->color = infra::ui::Color(0,0,0);
                            break;
                        }
                    }
                    rectangle->rect = { ui_pos.x, ui_pos.y, scale_tile_size, scale_tile_size};
                    frame.constant_items.push_back(std::move(rectangle));
                }
            }
        }


        for (const auto& entity : model.coins()) {
            const float half_size = entity->size() * 0.5f;
            const float scale_size = entity->size() * scale;

            infra::math::Point2 center = entity->position();
            // Position conversion: center -> top left
            infra::math::Point2 top_left{
                center.x - half_size,
                center.y - half_size
            };

            const infra::math::Point2 ui_pos = world_to_ui(top_left, offset, scale);
            auto sprite = std::make_unique<view::ui::RI_Sprite>();
            sprite->sprite = entity->name();
            sprite->rect = { ui_pos.x, ui_pos.y, scale_size, scale_size};
            frame.temp_items.push_back(std::move(sprite));
        }


        for (const auto& entity : model.power_pellets()) {

            const float half_size = entity->size() * 0.5f;
            const float scale_size = entity->size() * scale;

            infra::math::Point2 center = entity->position();
            // Position conversion: center -> top left
            infra::math::Point2 top_left{
                center.x - half_size,
                center.y - half_size
            };

            const infra::math::Point2 ui_pos = world_to_ui(top_left, offset, scale);

            auto sprite = std::make_unique<view::ui::RI_Sprite>();
            sprite->sprite = entity->name();
            sprite->rect = { ui_pos.x, ui_pos.y, scale_size, scale_size};
            frame.temp_items.push_back(std::move(sprite));
        }
        for (const auto& ghost : model.ghosts()){

            const auto& entity = ghost;
            const float half_size = entity->size() * 0.5f;
            const float scale_size = entity->size() * scale;

            infra::math::Point2 center = entity->position();
            // Position conversion: center -> top left
            infra::math::Point2 top_left{
                center.x - half_size,
                center.y - half_size
            };
            const infra::math::Point2 ui_pos = world_to_ui(top_left, offset, scale);
            auto sprite = std::make_unique<view::ui::RI_ComplexSprite>();
            sprite->sprite = entity->name();
            sprite->direction = entity->get_direction();

            if (!ghost->is_weak()) {
                sprite->status = infra::Status::Alive;
            }else {
                if (ghost->debuff_duration() > 2.f) {
                    sprite->status = infra::Status::Weak;
                }else {
                    sprite->status = infra::Status::SlightlyWeak;
                }
            }
            sprite->rect = { ui_pos.x, ui_pos.y, scale_size, scale_size};
            frame.temp_items.push_back(std::move(sprite));
        }
        {
            const auto& entity = model.pacman();
            const float half_size = entity->size() * 0.5f;
            const float scale_size = entity->size() * scale;

            infra::math::Point2 center = entity->position();
            // Position conversion: center -> top left
            infra::math::Point2 top_left{
                center.x - half_size,
                center.y - half_size
            };
            const infra::math::Point2 ui_pos = world_to_ui(top_left, offset, scale);
            auto sprite = std::make_unique<view::ui::RI_ComplexSprite>();
            sprite->sprite = entity->name();
            sprite->direction = entity->get_direction();
            sprite->status = model.pacman_status();
            sprite->rect = { ui_pos.x, ui_pos.y, scale_size, scale_size};
            frame.temp_items.push_back(std::move(sprite));
        }

    }
}
