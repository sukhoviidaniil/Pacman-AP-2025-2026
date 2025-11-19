/***************************************************************
 * Project:       Pacman
 * File:          Status_Info.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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
#ifndef PACMAN_STATUS_INFO_H
#define PACMAN_STATUS_INFO_H

#include "Expression_Info.h"

namespace Graphics::Info {

    struct rec_Info {
        unsigned int base = 0;
        unsigned int increase = 0;
    };
    inline void from_json(const nlohmann::json& j, rec_Info& s) {
        s.base = j.value<unsigned int>("base", 0);
        s.increase = j.value<unsigned int>("increase", 0);
    }

    class Status_Info {
    public:
        std::vector<Expression_Info> facial_expressions;
        int number_of_expressions_per_direction = 1;
        rec_Info recLeft;
        rec_Info recTop;

        Status_Info() = default;
        explicit Status_Info (const nlohmann::json& j);
    };


    inline void from_json(const nlohmann::json& j, Status_Info& s) {
        s.facial_expressions.resize(j["facial_expressions"].size());
        for (auto& obj : j["facial_expressions"]) {
            s.facial_expressions.push_back(obj.get<Expression_Info>());
        }
        s.number_of_expressions_per_direction = j.value("number_of_expressions_per_direction", 1);
        s.recLeft = j["recLeft"].get<rec_Info>();
        s.recTop = j["recTop"].get<rec_Info>();
    }
}

#endif //PACMAN_STATUS_INFO_H