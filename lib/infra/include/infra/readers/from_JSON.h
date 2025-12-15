/***************************************************************
 * Project:       Pacman
 * File:          from_JSON.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-11
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
#ifndef PACMAN_FROM_JSON_H
#define PACMAN_FROM_JSON_H

#include "json.hpp"
#include "infra/ast/Sprite_Expression.h"
#include "infra/ast/Sprite_Rec.h"
#include "infra/ast/Sprite_Status.h"

#include "infra/math/Point2.h"
#include "infra/math/Vector2.h"

namespace math {
    inline void from_json(const nlohmann::json& j, Point2& v) {
        v.x = j.at("x").get<float>();
        v.y = j.at("y").get<float>();
    }

    inline void from_json(const nlohmann::json& j, Vector2 & v) {
        v.x = j.at("x").get<float>();
        v.y = j.at("y").get<float>();
    }
}

namespace infra::ast {

    inline void from_json(const nlohmann::json& j, Sprite_Expression& s) {
        s.name = j.value("expression", "None");

        if (j.contains("direction")) from_json(j.at("direction"), s.direction);

        s.recLeft = j.value("recLeft", -1);
        s.recTop  = j.value("recTop", -1);
    }

    inline void from_json(const nlohmann::json& j, Sprite_Rec& s) {
        s.base = j.value<int>("base", -1);
        s.increase = j.value<int>("increase", -1);
    }

    inline void from_json(const nlohmann::json& j, Sprite_Status& s) {
        if (j.contains("facial_expressions") && j["facial_expressions"].is_array()) {
            s.facial_expressions.clear();
            s.facial_expressions.reserve(j["facial_expressions"].size());

            for (const auto& obj : j["facial_expressions"]) {
                s.facial_expressions.push_back(obj.get<Sprite_Expression>());
            }
        }
        s.number_of_expressions_per_direction = j.value("number_of_expressions_per_direction", 1);
        if (j.contains("recLeft")) from_json(j.at("recLeft"), s.recLeft);

        if (j.contains("recTop")) from_json(j.at("recTop"), s.recTop);
    }
}

#endif //PACMAN_FROM_JSON_H