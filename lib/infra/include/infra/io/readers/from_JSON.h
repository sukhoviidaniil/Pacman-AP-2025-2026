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
#include "infra/diagnostics/Logger.h"
#include "infra/math/Point2.h"
#include "infra/math/Vector2.h"
#include "infra/ast/model/Model.h"

#include "infra/ast/view/View.h"
#include "infra/ast/view/external/Sprite_Direction.h"
#include "infra/ast/view/external/Sprite_Rec.h"
#include "infra/ast/view/external/SpriteStatus.h"
#include "infra/ast/view/sprites/ComplexSprite.h"
#include "infra/ast/view/sprites/Sprite.h"

namespace infra::math {
    inline void from_json(const nlohmann::json& j, Point2& v) {
        v.x = j.at("x").get<float>();
        v.y = j.at("y").get<float>();
    }

    inline void from_json(const nlohmann::json& j, Vector2 & v) {
        v.x = j.at("x").get<float>();
        v.y = j.at("y").get<float>();
    }


    inline Direction parse_Direction(const std::string& name) {
        if (name == "Any") return Direction::Any;
        if (name == "Left") return Direction::Left;
        if (name == "Right") return Direction::Right;
        if (name == "Up") return Direction::Up;
        if (name == "Down") return Direction::Down;
        throw std::runtime_error("Unknown tile");
    }

}

namespace infra::io {

    inline nlohmann::json get_json_data(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            const std::string error = "File not found: " + filename + "!\n";
            LOG(error);
            throw std::runtime_error(error);
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
    const nlohmann::json &j,
    const std::string &key,
    const T &default_value
    ) {
        // Key not found -> return default
        if (!j.contains(key))
            return default_value;

        const auto& value = j.at(key);

        // If the JSON value type is correct -> return it
        try {
            return value.get<T>();
        }
        catch (const std::exception& e) {
            LOG(e.what());
            throw;
        }
    }

    template<class T>
    T get_checked(
        const nlohmann::json &j,
        const std::string &key
        ) {
        // Key not found -> err
        if (!j.contains(key)) {
            const std::string error = "nlohmann::json " + key + " parameter missing or invalid;";
            LOG(error);
            throw std::runtime_error(error);
        }
        // If the JSON value type is correct -> return it
        try {
            return j.at(key).get<T>();
        } catch (const std::exception& e) {
            LOG(e.what());
            throw;
        }
    }


    template<class T>
    T get_checked(
    const nlohmann::json &j
    ) {
        // If the JSON value type is correct -> return it
        try {
            return j.get<T>();
        } catch (const std::exception& e) {
            LOG(e.what());
            throw;
        }
    }

}

namespace infra::ast {

    inline void from_json(const nlohmann::json& j, Sprite& s) {
        // TODO IF NEEDED
    }

    inline void from_json(const nlohmann::json& j, Sprite_Direction& s) {
        const auto d_name = io::get_checked<std::string>(j, "direction");
        s.direction = math::parse_Direction(d_name);
        s.recLeft = io::get_checked<int>(j, "recLeft", s.recLeft);
        s.recTop  = io::get_checked<int>(j,"recTop", s.recTop);
    }

    inline void from_json(const nlohmann::json& j, Sprite_Rec& s) {
        s.base = io::get_checked<int>(j, "base", s.base);
        s.increase = io::get_checked<int>(j, "increase", s.increase);
    }

    inline void from_json(const nlohmann::json& j, SpriteStatus& s) {
        s.sprite_directions = io::get_checked<std::vector<Sprite_Direction>>(j, "Directions", s.sprite_directions);
        s.sprites_per_direction = io::get_checked<unsigned int>(j, "NSprites_per_direction", s.sprites_per_direction);
        s.recLeft = io::get_checked<Sprite_Rec>(j, "recLeft", s.recLeft);
        s.recTop = io::get_checked<Sprite_Rec>(j, "recTop", s.recLeft);
    }


    inline Status parse_Status(const std::string& s) {
        if (s == "Dead")  return Status::Dead;
        if (s == "Alive")  return Status::Alive;
        if (s == "Powered")  return Status::Powered;
        if (s == "Weak")  return Status::Weak;
        if (s == "SlightlyWeak")  return Status::SlightlyWeak;
        throw std::runtime_error("Unknown Status");
    }

    inline void from_json(const nlohmann::json& j, ComplexSprite& s) {
        s.using_texture = io::get_checked<std::string>(j, "using_texture", s.using_texture);
        s.sprits_width = io::get_checked<unsigned int>(j,"sprits_width",  s.sprits_width);
        s.sprits_height = io::get_checked<unsigned int>(j, "sprits_height", s.sprits_height);
        s.groups_names = io::get_checked<std::vector<std::string>>(j, "groups_names", s.groups_names);
        if (j.contains("statuses") && j["statuses"].is_array()) {
            for (const auto& status : j["statuses"]) {
                std::string status_name = status["Status"];
                s.groups_[parse_Status(status_name)] = io::get_checked<SpriteStatus>(status);
            }
        }
    }

    inline void from_json(const nlohmann::json& j, View& s) {
        s.type = io::get_checked<std::string>(j,"type", s.type);
        s.window_width = io::get_checked<unsigned int>(j, "window_width", s.window_width );
        s.window_height = io::get_checked<unsigned int>(j, "window_height", s.window_height);
        s.textures = io::get_checked<std::vector<std::string>>(j, "textures", s.textures);
    }

    inline Tile parse_tile(const std::string& s) {
        if (s == "Wall")  return Tile::Wall;
        if (s == "PacmanSpawn")  return Tile::PacmanSpawn;
        if (s == "GhostSpawn")  return Tile::GhostSpawn;
        if (s == "PowerPelletSpawn")  return Tile::PowerPelletSpawn;
        if (s == "CoinSpawn")  return Tile::CoinSpawn;
        if (s == "Empty") return Tile::Empty;
        throw std::runtime_error("Unknown tile");
    }

    inline void from_json(const nlohmann::json& json, Grid& s) {
        // rows x columns
        s.rows = io::get_checked<unsigned int>(json, "rows", s.rows);
        s.columns = io::get_checked<unsigned int>(json, "columns", s.columns);
        s.tile_size = io::get_checked<float>(json, "tile_size", s.tile_size);
        const auto grid = io::get_checked<std::vector<std::vector<std::string>>>(json, "grid");
        if (grid.size() != s.rows) {
            throw std::runtime_error("Grid size mismatch");
        }
        for (size_t i = 0; i < s.rows; ++i) {
            if (grid[i].size() != s.columns) {
                throw std::runtime_error("Grid size mismatch");
            }
        }
        s.grid.resize(s.rows, std::vector<Tile>(s.columns));
        for (size_t y = 0; y < s.rows; ++y) {
            for (size_t x = 0; x < s.columns; ++x) {
                // y -> rows
                // x -> columns
                s.grid[y][x] =  parse_tile(grid[y][x]);
            }
        }
    }

    inline void from_json(const nlohmann::json& json, PacmanSpawn& s) {
        s.size = io::get_checked<float>(json, "size", s.size);
        s.speed = io::get_checked<float>(json,"speed",  s.size);
    }

    inline void from_json(const nlohmann::json& j, Model& s) {
        s.grid = io::get_checked<Grid>(j, "Grid", s.grid);
        s.pacman_spawn = io::get_checked<PacmanSpawn>(j, "PacmanSpawn", s.pacman_spawn);

    }
}

#endif //PACMAN_FROM_JSON_H