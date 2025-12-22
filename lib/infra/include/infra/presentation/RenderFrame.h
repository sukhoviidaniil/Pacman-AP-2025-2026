/***************************************************************
 * Project:       Pacman
 * File:          RenderFrame.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-22
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
#ifndef PACMAN_RENDERFRAME_H
#define PACMAN_RENDERFRAME_H

#include "Animation.h"
#include "base/Color.h"
#include "infra/presentation/base/Rect.h"
#include "infra/math/Direction.h"

namespace infra::ui {
    enum class Space {
        Screen,   // UI, HUD
        World     // game logic
    };

    struct Camera {
        /// The size of the screen area in which View draws the scene. Screen pixels
        math::Vector2 viewport_size;
        /// Camera position in world coordinates
        math::Vector2 camera_pos;

        float camera_zoom = 1.f;
    };

    enum class ItemType {
        Text,
        Sprite,
        ComplexSprite
    };

    struct RenderItem {
        ItemType type;

        /// What coordinate system is used?
        Space space;
        /// Element dimensions
        Rect  rect;

        /**
         * @brief Name or ID of the sprite resource.
         */
        std::string sprite;

        /**
         * @brief Optional direction (e.g., "up", "down", "left", "right").
         * Can be empty if not needed.
         */
        math::Direction direction;

        /**
         * @brief Optional status (e.g., "idle", "walking", "attacking").
         * Can be empty if not needed.
         */
        std::string status;

        std::optional<Animation> animation;

        std::string text;
        Color color;
    };

    struct RenderFrame {
        Camera camera;
        std::vector<RenderItem> items;
    };

    struct RenderFrameGraph {
        bool redraw = false;
        std::vector<RenderFrame> constant_frames;
        std::vector<RenderFrame> temp_frames;
    };
}


#endif //PACMAN_RENDERFRAME_H