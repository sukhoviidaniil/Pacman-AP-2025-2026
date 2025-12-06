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
#include "Reader_JSON_Info.h"
namespace Core {

    class Reader_JSON final : public Reader {

        protected:

        static void add_Actor(
            const std::shared_ptr<const File_Reader> &fr,
            std::shared_ptr<World> &world,
            const nlohmann::json &model);
        void add_Actor (Entity_JSON_Info &conf) const;
        void Entity_Register(std::unordered_map<std::string, void(Reader_JSON::*)(Entity_JSON_Info &conf) const> &outMap) const;
        void add_Entity(
            Entity_JSON_Info& conf
            ) const;

        std::shared_ptr<Stage> load_Game_Stage(
            const Reader_JSON_Base_Info &conf
            ) const;

        static void Stage_Register(std::unordered_map<std::string, std::shared_ptr<Stage>(Reader_JSON::*)(const Reader_JSON_Base_Info &conf) const> &outMap);

        void HitBoxe_Register(std::unordered_map<std::string, void(Reader_JSON::*)(const Reader_JSON_Base_Info &conf) const> &outMap) const;

        static nlohmann::json get_json_data(
            const std::string &filename
            );

        public:
        Reader_JSON();
        ~Reader_JSON() override;

        void load_SFML_Sprite(
            const std::shared_ptr<Graphics::SFML_Manager>& sfml_manager,
            const std::string &filename
            ) const override;
        void load_SFML_Sprite_Group(
            const std::shared_ptr<Graphics::SFML_Manager>& sfml_manager,
            const std::string &filename
            ) const override;
        [[nodiscard]] std::shared_ptr<Graphics::SFML_Manager> load_SFML_Manager(
            const std::shared_ptr<const File_Reader> &fr,
            const std::string& filename
            ) const override;


        [[nodiscard]] std::shared_ptr<Logic::Collision::HitBoxe> load_HitBoxe(
            const std::string& filename
            ) const override;
        [[nodiscard]] std::shared_ptr<Graphics::Camera> load_Camera(
            const std::string& filename
            ) const override;

        void load_Entities(
            const std::shared_ptr<const File_Reader> &fr,
            std::shared_ptr<World> &world, const std::string &filename
            ) const;

        [[nodiscard]] std::shared_ptr<Logic::Tile_Grid> load_Tile_Grid(
            std::shared_ptr<Stage>& stage,
            const std::string& filename
            ) const override;

        [[nodiscard]] std::shared_ptr<Stage> load_Stage(
            const std::shared_ptr<const File_Reader>& fr, const std::string& path
            ) const override;

        [[nodiscard]] Stage_Manager load_Stage_Manager(
            const std::shared_ptr<const File_Reader>& fr,
            const std::string &path
            ) const override;

        [[nodiscard]] Info::Game_Info get_Game_Info(
            const std::string& filename
            ) override;
    };
}

#endif //PACMAN_READER_JSON_H