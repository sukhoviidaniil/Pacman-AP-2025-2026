/***************************************************************
 * Project:       Pacman
 * File:          Reader_JSON.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-26
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

#ifndef PACMAN_READER_JSON_H
#define PACMAN_READER_JSON_H

#include "core/readers/Reader.h"
#include "json.hpp"
#include "core/World.h"





namespace Core {

    static Math::Vector2 from_json(const nlohmann::json& j) {
        Math::Vector2 v;
        v.x = j.at("x").get<float>();
        v.y = j.at("y").get<float>();
        return v;
    }

    struct Entity_JSON_Info {
        const std::shared_ptr<File_Reader>& fr;
        const Graphics::SFML_Manager& manager;
        std::shared_ptr<World>& world;
        const nlohmann::json& info;
    };

    class Reader_JSON final : public Reader {
        protected:
        static void add_Actor(
            const std::shared_ptr<File_Reader> &fr,
            std::shared_ptr<World> &world,
            const nlohmann::json &model);
        void add_Actor (const Entity_JSON_Info &conf);
        static void Entity_Register(std::unordered_map<std::string, void(Reader_JSON::*)(const Entity_JSON_Info &conf)> &outMap);
        void add_Entity(const Entity_JSON_Info& conf) const;
        static nlohmann::json get_json_data(const std::string &filename);

        public:
        Reader_JSON();
        ~Reader_JSON() override;

        void load_SFML_Sprite(Graphics::SFML_Manager &manager, const std::string &filename) const override;
        void load_SFML_Sprite_Group(Graphics::SFML_Manager &manager, const std::string &filename) const override;
        [[nodiscard]] std::shared_ptr<Logic::Collision::HitBoxe> make_hitboxe(const std::string& filename) const override;
        [[nodiscard]] std::shared_ptr<Graphics::Camera> make_Camera(const std::string& filename) const override;

        void load_Entities(
            const std::shared_ptr<File_Reader> &fr,
            const Graphics::SFML_Manager &manager,
            std::shared_ptr<World> &world, const std::string &filename) const;

        [[nodiscard]] std::shared_ptr<Logic::Tile_Grid> make_Tile_Grid(
            std::shared_ptr<Info::Validation>& info,
            std::shared_ptr<Stage>& stage,
            const Graphics::SFML_Manager& manage, const std::string& filename) const override;

        [[nodiscard]] std::shared_ptr<Stage> make_Stage(
            std::shared_ptr<Info::Validation>& info,
            const std::shared_ptr<File_Reader>& fr,
            const Graphics::SFML_Manager& manage, const std::string& filename) const override;

        [[nodiscard]] Stage_Manager make_Stage_Manager(
            const std::shared_ptr<File_Reader>& fr,
            const Graphics::SFML_Manager& manager, const std::string &path) override;

        [[nodiscard]] Info::Game_Info get_Game_Info(const std::string& filename) override;
    };
}

#endif //PACMAN_READER_JSON_H