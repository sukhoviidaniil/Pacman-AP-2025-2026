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

namespace Core {
    class Reader_JSON final : public Reader {
        protected:

        static nlohmann::json get_json_data(const std::string &filename);

        public:
        Reader_JSON();
        ~Reader_JSON() override;

        void load_SFML_Sprite(Graphics::SFML_Manager &manager, const std::string &filename) const override;

        void load_SFML_Sprite_Group(Graphics::SFML_Manager &manager, const std::string &filename) const override;

        [[nodiscard]] std::shared_ptr<Graphics::Camera> make_Camera(
            const std::string& filename) const override;

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
            const Graphics::SFML_Manager& manage, const std::string &path) override;
    };
}

#endif //PACMAN_READER_JSON_H