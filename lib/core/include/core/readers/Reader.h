/***************************************************************
 * Project:       Pacman
 * File:          Reader.h
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
#ifndef PACMAN_READER_H
#define PACMAN_READER_H

#include "core/Stage_Manager.h"
#include "core/info/Game_Info.h"
#include "core/info/Validation.h"
#include "graphics/Camera.h"
#include "graphics/SFML_Manager.h"
#include "logic/Tile_Grid.h"

namespace Core {
    class File_Reader;
    class Reader {
        public:
        virtual ~Reader() = default;

        virtual void load_SFML_Sprite(Graphics::SFML_Manager& manager, const std::string& filename) const = 0;
        virtual void load_SFML_Sprite_Group(Graphics::SFML_Manager& manager, const std::string& filename) const = 0;


        [[nodiscard]] virtual std::shared_ptr<Logic::Collision::HitBoxe> make_hitboxe(const std::string& filename) const = 0;

        [[nodiscard]] virtual std::shared_ptr<Graphics::Camera> make_Camera(
            const std::string& filename) const = 0;

        [[nodiscard]] virtual std::shared_ptr<Logic::Tile_Grid> make_Tile_Grid(
            std::shared_ptr<Info::Validation>& info,
            std::shared_ptr<Stage>& stage,
            const Graphics::SFML_Manager &manage, const std::string& filename) const = 0;

        [[nodiscard]] virtual std::shared_ptr<Stage> make_Stage(
            std::shared_ptr<Info::Validation>& info,
            const std::shared_ptr<File_Reader>& fr,
            const Graphics::SFML_Manager& manage, const std::string& filename) const = 0;

        virtual Stage_Manager make_Stage_Manager(
            const std::shared_ptr<File_Reader>& fr,
            const Graphics::SFML_Manager& manage, const std::string& path) = 0;

        virtual Info::Game_Info get_Game_Info(const std::string& filename) = 0;

    };
}

#endif //PACMAN_READER_H