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

        const model::Tile_Grid &grid = model.grid();
        const float ts = grid.tile_size();

        // Map size in world coordinates (taking into account the full size of the tiles)
        const float width  = grid.get_width();
        const float height = grid.get_height();
        infra::ui::Rect world_bounds{ 0.f, 0.f, width, height};

        const auto& tiles = grid.get_tiles();

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
            for (size_t y = 0; y < tiles.size(); ++y) {
                for (size_t x = 0; x < tiles[y].size(); ++x) {
                    auto tile = tiles[y][x];
                    if (!tile) continue;

                    infra::math::Point2 tp = tile->position();

                    // Position conversion: tile center -> top left
                    infra::math::Point2 top_left{
                        tp.x - ts * 0.5f,
                        tp.y - ts * 0.5f
                    };

                    /*
                    // Check that the tile is inside world_bounds
                    float left   = tp.x - ts * 0.5f;
                    float right  = tp.x + ts * 0.5f;
                    float top    = tp.y - ts * 0.5f;
                    float bottom = tp.y + ts * 0.5f;

                    if (right < world_bounds.x || left > world_bounds.x + world_bounds.width ||
                        bottom < world_bounds.y || top > world_bounds.y + world_bounds.height) {
                        continue;
                        }
                        */

                    // Convert to UI coordinates
                    const infra::math::Point2 ui_pos = world_to_ui(top_left, offset, scale);

                    auto rectangle = std::make_unique<view::ui::RI_Rectangle>();
                    rectangle->color = tile->walkable() ? infra::ui::Color(0,0,0) : infra::ui::Color(0,0,255);
                    rectangle->rect = { ui_pos.x, ui_pos.y, ts * scale, ts * scale };

                    frame.constant_items.push_back(std::move(rectangle));
                }
            }
        }
    }
}
