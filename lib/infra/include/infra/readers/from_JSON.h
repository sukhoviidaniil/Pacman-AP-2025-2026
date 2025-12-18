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
#include "infra/loger/Logger.h"
#include "infra/ast/view/Sprite_Expression.h"
#include "infra/ast/view/Sprite_Rec.h"
#include "infra/ast/view/Sprite_Status.h"

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

namespace infra {

    inline nlohmann::json get_json_data(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::string error = "File not found: " + filename + "!\n";
            LOG(error);
            throw std::runtime_error("File not opened");
        }
        nlohmann::json data;
        file >> data;
        file.close();
        return data;
    }

    inline void invalid_parameter(const std::string &path, const std::string &name, const std::string &object) {
        const std::string error = "File " + path + " parameter " + name + " in " + object + " missing or invalid;";
        LOG(error);
        throw std::runtime_error(error);
    }

    template<class T>
    T get_checked(
    const T &default_value,
    const std::string &key,
    const nlohmann::json &j,
    const std::string &path = "",
    const std::string &object = "ROOT"
    ) {
        // Key not found -> return default
        if (!j.contains(key))
            return default_value;

        const auto& value = j.at(key);

        // If the JSON value type is correct -> return it
        try {
            return value.get<T>();
        }
        catch (...) {
            invalid_parameter(path, key, object);
        }
        throw;
    }

    template<class T>
    T get_checked(
        const std::string &key,
        const nlohmann::json &j,
        const std::string &path,
        const std::string &object = "ROOT"
        ) {
        // Key not found -> err
        if (!j.contains(key)) {
            invalid_parameter(path, key, object);
        }
        // If the JSON value type is correct -> return it
        try {
            return j.at(key).get<T>();
        } catch (...) {
            invalid_parameter(path, key, object);
        }
        throw;
    }

    template<class T>
    T get_checked(
    const nlohmann::json &j,
    const std::string &path,
    const std::string &object
    ) {
        // If the JSON value type is correct -> return it
        try {
            return j.get<T>();
        } catch (...) {
            invalid_parameter(path, "ROOT", object);
        }
        throw;
    }
}

namespace infra::ast {

    inline void from_json(const nlohmann::json& j, Sprite& s) {
        // TODO IF NEEDED
    }

    inline void from_json(const nlohmann::json& j, Sprite_Expression& s) {
        s.name = get_checked<std::string>(s.name , "expression", j);
        s.direction = get_checked<math::Vector2>(s.direction , "direction", j);
        s.recLeft = get_checked<int>(s.recLeft , "recLeft", j);
        s.recTop  = get_checked<int>(s.recTop , "recTop", j);
    }

    inline void from_json(const nlohmann::json& j, Sprite_Rec& s) {
        s.base = get_checked<int>(s.base , "base", j);
        s.increase = get_checked<int>(s.increase , "increase", j);
    }

    inline void from_json(const nlohmann::json& j, Sprite_Status& s) {
        s.facial_expressions = get_checked<std::vector<Sprite_Expression>>(s.facial_expressions, "facial_expressions", j);
        s.number_of_expressions_per_direction = get_checked<unsigned int>(s.number_of_expressions_per_direction, "number_of_expressions_per_direction", j);
        s.recLeft = get_checked<Sprite_Rec>(s.recLeft, "recLeft", j);
        s.recTop = get_checked<Sprite_Rec>(s.recLeft, "recTop", j);
    }

    inline void from_json(const nlohmann::json& j, ast::Complex_Sprite& s) {
        s.using_texture = get_checked<std::string>(s.using_texture, "using_texture", j);
        s.sprits_width = get_checked<unsigned int>(s.sprits_width, "sprits_width", j);
        s.sprits_height = get_checked<unsigned int>(s.sprits_height, "sprits_height", j);
        s.groups_names = get_checked<std::vector<std::string>>(s.groups_names ,"groups_names", j);
        s.number_of_statuses = get_checked<unsigned int>(s.number_of_statuses, "number_of_statuses", j);
        s.sprite_statuses = get_checked<std::vector<Sprite_Status>>(s.sprite_statuses ,"statuses", j);
    }

    inline void from_json(const nlohmann::json& j, View& s) {
        s.type = get_checked<std::string>(s.type , "type", j);
        s.window_width = get_checked<unsigned int>(s.window_width , "window_width", j);
        s.window_height = get_checked<unsigned int>(s.window_height , "window_height", j);
        s.textures = get_checked<std::vector<std::string>>(s.textures, "textures", j);
        s.sprites = get_checked<std::vector<ast::Sprite>>(s.sprites, "sprites", j);
        s.complex_sprites = get_checked<std::vector<ast::Complex_Sprite>>(s.complex_sprites, "sprite_groups", j);
    }

    inline void from_json(const nlohmann::json& j, Model& s) {
        s.columns = get_checked<unsigned int>(s.columns , "columns", j);
        s.rows = get_checked<unsigned int>(s.rows , "rows", j);
        s.grid = get_checked<std::vector<std::vector<std::string>>>(s.grid , "grid", j);
    }
}

#endif //PACMAN_FROM_JSON_H