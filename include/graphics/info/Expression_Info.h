/***************************************************************
 * Project:       Pacman
 * File:          Expression_Info.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-09
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
#ifndef PACMAN_EXPRESSION_INFO_H
#define PACMAN_EXPRESSION_INFO_H
#include "math/Vector2.h"
#include "func/json.hpp"
#include <string>

namespace Graphics::Info {
    class Expression_Info {
    public:
        std::string expression;
        Math::Vector2 direction;
        int recLeft = -1, recTop = -1;
        Expression_Info() = default;
    };

    inline void from_json(const nlohmann::json& j, Expression_Info& s) {
        s.expression = j.value("expression", "");
        const std::vector<float> tepm_direction = j.value("direction", std::vector<float>{0,0});
        if (tepm_direction.size() != 2) {
            throw std::runtime_error("Expression_Info:: direction - invalid");
        }
        s.direction  = Math::Vector2(tepm_direction[0], tepm_direction[1]);
        s.recLeft    = j.value("recLeft", -1);
        s.recTop     = j.value("recTop", -1);
    }
}

#endif //PACMAN_EXPRESSION_INFO_H