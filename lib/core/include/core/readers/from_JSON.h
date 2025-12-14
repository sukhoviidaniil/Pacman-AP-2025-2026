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

#include "core/info/Expression_Info.h"
#include "json.hpp"
#include "core/info/rec_Info.h"
#include "core/info/Status_Info.h"

namespace core{




    inline void from_json(const nlohmann::json& j, Expression_Info& s) {
        s.expression = j.value("expression", "");
        const std::vector<float> tepm_direction = j.value("direction", std::vector<float>{0,0});
        if (tepm_direction.size() != 2) {
            throw std::runtime_error("Expression_Info:: direction - invalid");
        }
        s.direction  = math::Vector2(tepm_direction[0], tepm_direction[1]);
        s.recLeft    = j.value("recLeft", -1);
        s.recTop     = j.value("recTop", -1);
    }

    static math::Vector2 from_json(const nlohmann::json& j) {
        math::Vector2 v;
        v.x = j.at("x").get<float>();
        v.y = j.at("y").get<float>();
        return v;
    }

    inline void from_json(const nlohmann::json& j, rec_Info& s) {
        s.base = j.value<unsigned int>("base", 0);
        s.increase = j.value<unsigned int>("increase", 0);
    }

    inline void from_json(const nlohmann::json& j, Status_Info& s) {
        s.facial_expressions.reserve(j["facial_expressions"].size());
        for (auto& obj : j["facial_expressions"]) {
            s.facial_expressions.push_back(obj.get<Expression_Info>());
        }
        s.number_of_expressions_per_direction = j.value("number_of_expressions_per_direction", 1);
        s.recLeft = j.value("recLeft", rec_Info());
        s.recTop = j.value("recTop", rec_Info());
    }
}

#endif //PACMAN_FROM_JSON_H