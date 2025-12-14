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

#include "core/Reader.h"
#include "Reader_JSON_Info.h"

namespace core {
    class Reader_JSON final : public Reader {
    public:
        Reader_JSON();
        ~Reader_JSON() override;

        void load_SFML_Sprite(
            const std::shared_ptr<graphics::SFML_Manager>& sfml_manager,
            const std::string &filename
            ) const override;
        void load_SFML_Sprite_Group(
            const std::shared_ptr<graphics::SFML_Manager>& sfml_manager,
            const std::string &filename
            ) const override;
        [[nodiscard]] std::shared_ptr<graphics::SFML_Manager> load_SFML_Manager(
            const std::shared_ptr<const File_Reader> &fr,
            const std::string& filename
            ) const override;

        [[nodiscard]] logic::collision::HitBoxe_Info load_HitBoxe(
            const std::string& path
            ) const override;
        [[nodiscard]] graphics::Camera_Info load_Camera(
            const std::string& path
            ) const override;


        void load_Entities(
            const std::shared_ptr<const File_Reader> &fr,
            const std::shared_ptr<Stage> &stage,
            const std::shared_ptr<logic::Tile_Grid> &grid,
            const std::string &path
            ) const override;

        [[nodiscard]] graphics::Tile_Grid_Pair load_Tile_Grid(
            std::shared_ptr<graphics::SFML_Manager> sfml_manager,
            const std::string& path
            ) const override;

        [[nodiscard]] std::shared_ptr<Stage> load_Stage(
            const std::shared_ptr<const File_Reader>& fr, const std::string& path
            ) const override;

        [[nodiscard]] Stage_Manager load_Stage_Manager(
            const std::shared_ptr<const File_Reader>& fr,
            const std::string &path
            ) const override;

        [[nodiscard]] Game_Info get_Game_Info(
            const std::string& path
            ) override;

    protected:

        std::shared_ptr<logic::model::Entity> load_Actor (Stage_Info_JSON &conf, const std::shared_ptr<logic::Tile_Grid> &grid) const;
        void Entity_Register(std::unordered_map<std::string, std::shared_ptr<logic::model::Entity>(Reader_JSON::*)(Stage_Info_JSON &conf, const std::shared_ptr<logic::Tile_Grid> &grid) const> &outMap) const;
        void load_Entity(
            Stage_Info_JSON& conf,
            const std::shared_ptr<logic::Tile_Grid> &grid
            ) const;

        void Entity_Register(std::unordered_map<std::string, std::shared_ptr<logic::model::Entity>(Reader_JSON::*)(Stage_Info_JSON &conf) const> &outMap) const;

        [[nodiscard]] std::shared_ptr<Stage> load_Game_Stage(
            const Reader_Base_Info_JSON &conf
            ) const;

        static void Stage_Register(std::unordered_map<std::string, std::shared_ptr<Stage>(Reader_JSON::*)(const Reader_Base_Info_JSON &conf) const> &outMap);

        [[nodiscard]] std::shared_ptr<logic::collision::HitBoxe> load_HitBox_Rectangle(const nlohmann::json& data) const;
        void HitBoxe_Register(std::unordered_map<std::string, std::shared_ptr<logic::collision::HitBoxe>(Reader_JSON::*)(const nlohmann::json& info) const> &outMap) const;

        template<class T>
        static T get_checked(
            const T &default_value,
            const nlohmann::json &j,
            const std::string &key,
            const std::string &path,
            const std::string &object = "ROOT"
            );

        template<class T>
        static T get_checked(
            const nlohmann::json &j,
            const std::string &key,
            const std::string &path,
            const std::string &object = "ROOT"
            );

        static void invalid_parameter(const std::string &path, const std::string &name, const std::string &object);
        static nlohmann::json get_json_data(
            const std::string &filename
            );
    };
}

#endif //PACMAN_READER_JSON_H