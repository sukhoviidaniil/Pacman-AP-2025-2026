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
#include "infra/ast/view/internal/Sprite_Direction.h"
#include "infra/ast/view/internal/Sprite_Rec.h"
#include "infra/ast/view/internal/SpriteStatus.h"
#include "infra/ast/view/sprites/ComplexSprite.h"
#include "infra/ast/view/sprites/Sprite.h"
#include "infra/ast/view/sprites/SpriteList.h"

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

    inline void invalid_parameter(const std::string &path, const std::string &object, const std::string &name) {
        const std::string error = "File: " + path+ ", in " + object +  ", parameter " + name + " missing or invalid;";
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

    // ---------------- ScoreSetup ----------------
    inline void from_json(const nlohmann::json& j, ScoreSetup& s) {
        // --- Base ---
        s.lives_remaining = io::get_checked(j, "lives_remaining", s.lives_remaining);
        s.level          = io::get_checked(j, "level", s.level);
        s.points_score   = io::get_checked(j, "points_score", s.points_score);

        // --- Coins ---
        s.time_since_the_last_coin_collection =
            io::get_checked(j, "time_since_the_last_coin_collection",
                            s.time_since_the_last_coin_collection);

        s.coin_award_amount =
            io::get_checked(j, "coin_award_amount", s.coin_award_amount);
        s.coin_max_award_level =
            io::get_checked(j, "coin_max_award_level", s.coin_max_award_level);
        s.coin_award_level =
            io::get_checked(j, "coin_award_level", s.coin_award_level);

        s.coin_RR_Time_until_reduction =
            io::get_checked(j, "coin_RR_Time_until_reduction",
                            s.coin_RR_Time_until_reduction);
        s.coin_RR_Time_between_reductions =
            io::get_checked(j, "coin_RR_Time_between_reductions",
                            s.coin_RR_Time_between_reductions);

        // --- Ghosts ---
        s.time_since_the_last_ghost_collection =
            io::get_checked(j, "time_since_the_last_ghost_collection",
                            s.time_since_the_last_ghost_collection);

        s.ghost_award_amount =
            io::get_checked(j, "ghost_award_amount", s.ghost_award_amount);
        s.ghost_max_award_level =
            io::get_checked(j, "ghost_max_award_level", s.ghost_max_award_level);
        s.ghost_award_level =
            io::get_checked(j, "ghost_award_level", s.ghost_award_level);

        s.ghost_RR_Time_until_reset =
            io::get_checked(j, "ghost_RR_Time_until_reset",
                            s.ghost_RR_Time_until_reset);
    }

    // ---------------- ScoreInfo ----------------
    inline void from_json(const nlohmann::json& j, ScoreInfo& s) {
        s.id             = io::get_checked<std::uint64_t>(j, "id", s.id);
        s.lives_remaining =
            io::get_checked<unsigned int>(j, "lives_remaining", s.lives_remaining);
        s.level =
            io::get_checked<unsigned int>(j, "level", s.level);
        s.points_score =
            io::get_checked<unsigned int>(j, "points_score", s.points_score);
    }

    // ---------------- ScoreBord ----------------
    inline void from_json(const nlohmann::json& j, ScoreBord& bord) {
        bord.file      = io::get_checked(j, "file", bord.file);
        bord.bord_size = io::get_checked<size_t>(j, "bord_size", bord.bord_size);

        // Score setup
        if (j.contains("score_setup")) {
            bord.score_setup = io::get_checked<ScoreSetup>(j, "score_setup");
        }

        // Scores
        bord.scores.clear();
        if (j.contains("scores") && j["scores"].is_array()) {
            for (const auto& item : j["scores"]) {
                bord.scores.push_back(io::get_checked<ScoreInfo>(item));
            }
        }
    }


    inline void from_json(const nlohmann::json& j, Texture& s) {
        s.name = io::get_checked<std::string>(j, "name");
        s.file = io::get_checked<std::string>(j, "file");
    }

    inline void from_json(const nlohmann::json& j, Font& s) {
        s.font = io::get_checked<std::string>(j, "font");
        s.file = io::get_checked<std::string>(j, "file");
    }

    inline void from_json(const nlohmann::json& j, Sprite& s) {
        // SpriteNode
        s.using_texture = io::get_checked<std::string>(j, "using_texture");
        s.sprits_width = io::get_checked<unsigned int>(j, "sprits_width");
        s.sprits_height = io::get_checked<unsigned int>(j, "sprits_height");
        // Sprite
        s.name = io::get_checked<std::string>(j, "name");
        s.recLeft = io::get_checked<int>(j, "recLeft");
        s.recTop = io::get_checked<int>(j, "recTop");
    }

    inline void from_json(const nlohmann::json& j, SpriteList& s) {
        // SpriteNode
        s.using_texture = io::get_checked<std::string>(j, "using_texture");
        s.sprits_width = io::get_checked<unsigned int>(j, "sprits_width");
        s.sprits_height = io::get_checked<unsigned int>(j, "sprits_height");
        // Sprite
        s.names = io::get_checked<std::vector<std::string>>(j, "names");
        s.recLeft = io::get_checked<ast::Sprite_Rec>(j, "recLeft");
        s.recTop = io::get_checked<ast::Sprite_Rec>(j, "recTop");
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

    inline void from_json(const nlohmann::json& j, Animation& s) {
        s.size = io::get_checked<size_t>(j, "size", s.size);
        s.frame_duration = io::get_checked<float>(j, "frame_duration", s.frame_duration);
        s.recLeft_increase = io::get_checked<int>(j, "recLeft_increase", s.recLeft_increase);
        s.recTop_increase = io::get_checked<int>(j, "recTop_increase", s.recTop_increase);
    }

    inline void from_json(const nlohmann::json& j, SpriteStatus& s) {
        s.sprite_directions = io::get_checked<std::vector<Sprite_Direction>>(j, "Directions", s.sprite_directions);
        s.animation = io::get_checked<Animation>(j, "Animation", s.animation);
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
        s.fps = io::get_checked<int>(j,"fps", s.fps);
        s.view_directory = io::get_checked<std::string>(j, "view_directory", s.view_directory);
        s.textures = io::get_checked<std::vector<Texture>>(j, "Textures");
        s.fonts = io::get_checked<std::vector<Font>>(j, "Fonts");
    }

    inline Tile parse_tile(const std::string& s) {
        if (s == "W")  return Tile::Wall;
        if (s == "M")  return Tile::PacmanSpawn;
        if (s == "G")  return Tile::GhostSpawn;
        if (s == "P")  return Tile::PowerPelletSpawn;
        if (s == "C")  return Tile::CoinSpawn;
        if (s == "F")  return Tile::Empty;
        if (s == "B")  return Tile::Barrier;
        throw std::runtime_error("Unknown tile");
    }

    inline void from_json(const nlohmann::json& json, Grid& s) {
        // rows x columns
        s.rows = io::get_checked<size_t>(json, "rows", s.rows);
        s.columns = io::get_checked<size_t>(json, "columns", s.columns);
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
        s.sprite_size = io::get_checked<float>(json, "sprite_size", s.sprite_size);
        s.speed = io::get_checked<float>(json,"speed",  s.speed);
    }

    inline PathFinderType parse_path_finder(const std::string& s) {
        if (s == "AStar")  return PathFinderType::AStar;
        if (s == "BFS")  return PathFinderType::BFS;
        if (s == "Greedy")  return PathFinderType::Greedy;
        throw std::runtime_error("Unknown PathFinder type");
    }

    inline void from_json(const nlohmann::json& json, GhostInfo& s) {
        s.sprite_size = io::get_checked<float>(json, "sprite_size", s.sprite_size);

        const auto path_finder = io::get_checked<std::string>(json, "path_finder", "BFS");
        s.path_finder = parse_path_finder(path_finder);

        s.base_speed= io::get_checked<float>(json,"base_speed", s.base_speed);
        s.frightened_speed= io::get_checked<float>(json,"frightened_speed", s.frightened_speed);
        s.eaten_speed= io::get_checked<float>(json,"eaten_speed", s.eaten_speed);
        s.start_amount= io::get_checked<int>(json,"start_amount", s.start_amount);
        s.amount_per_level= io::get_checked<float>(json,"amount_per_level", s.amount_per_level);
    }
    inline void from_json(const nlohmann::json& json, GhostSpawn& s) {
        s.Blinky = io::get_checked<GhostInfo>(json,"Blinky",  s.Blinky);
        s.Pinky = io::get_checked<GhostInfo>(json,"Pinky",  s.Pinky);
        s.Inky = io::get_checked<GhostInfo>(json,"Inky",  s.Inky);
        s.Clyde = io::get_checked<GhostInfo>(json,"Clyde",  s.Clyde);
    }
    inline void from_json(const nlohmann::json& json, CoinSpawn& s) {
        s.hitbox_size = io::get_checked<float>(json, "hitbox_size", s.hitbox_size);
        s.sprite_size = io::get_checked<float>(json, "sprite_size", s.sprite_size);
    }
    inline void from_json(const nlohmann::json& json, PowerPelletSpawn& s) {
        s.name = io::get_checked<std::string>(json, "name", s.name);
        s.buff_duration = io::get_checked<float>(json, "buff_duration", s.buff_duration);
        s.hitbox_size = io::get_checked<float>(json, "hitbox_size", s.hitbox_size);
        s.sprite_size = io::get_checked<float>(json, "sprite_size", s.sprite_size);
    }

    inline void from_json(const nlohmann::json& j, Model& s) {
        s.grid = io::get_checked<Grid>(j, "Grid", s.grid);
        s.pacman_spawn = io::get_checked<PacmanSpawn>(j, "PacmanSpawn", s.pacman_spawn);
        s.ghost_spawn = io::get_checked<GhostSpawn>(j, "GhostSpawn", s.ghost_spawn);
        s.coin_spawn = io::get_checked<CoinSpawn>(j, "CoinSpawn", s.coin_spawn);
        s.power_pellet_spawn = io::get_checked<PowerPelletSpawn>(j, "PowerPelletSpawn", s.power_pellet_spawn);
    }
}


#endif //PACMAN_FROM_JSON_H