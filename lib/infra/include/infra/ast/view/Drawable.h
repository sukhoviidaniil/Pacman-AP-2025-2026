/***************************************************************
 * Project:       Pacman
 * File:          Drawable.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-17
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
#ifndef PACMAN_DRAWABLE_H
#define PACMAN_DRAWABLE_H


#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../Node.h"
#include "infra/math/Point2.h"
#include "infra/math/Vector2.h"

namespace infra::ast {
    struct Color {
        std::uint8_t red = 0;
        std::uint8_t green = 0;
        std::uint8_t blue = 0;

        constexpr Color() = default;
        constexpr Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) : red(r), green(g), blue(b) {}
    };
    struct Border {
        unsigned int size = 0;
        Color color;
    };
    struct Transform {
        math::Point2 position;
        math::Vector2 scale {1.f, 1.f};
        float rotation = 0.f;
    };
    struct Drawable : View_Node{
        Transform transform;
    };
    struct Rectangle : Drawable {
        unsigned int width = 0;
        unsigned int height = 0;
        Color internal_color;
        std::optional<Border> border;
    };
    struct Text : Drawable {
        std::string text;
        Color color;
    };
    struct Scene_Entity : Drawable {
        std::string name_;
        std::optional<math::Vector2> direction;
        std::optional<int> status;
    };
    struct DrawableContainer : View_Node {
        std::vector<std::shared_ptr<Drawable>> info;
    };
    struct Scene_UI : DrawableContainer {
    };
    struct Scene_Model : DrawableContainer {
    };

    struct Scene_Graph {
        std::shared_ptr<Scene_UI> ui_layer;
        std::shared_ptr<Scene_Model> model_layer;
    };
}
#endif //PACMAN_DRAWABLE_H