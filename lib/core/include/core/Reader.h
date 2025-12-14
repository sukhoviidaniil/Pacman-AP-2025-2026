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
#include "graphics/Camera.h"
#include "graphics/Graphics_Factory.h"
#include "graphics/SFML_Manager.h"
#include "info/Game_Info.h"

namespace core {

    class File_Reader;

    struct Reader_Info {
        const std::shared_ptr<const File_Reader>& fr;
        const std::string& path;
    };

    class Reader {
        public:
        virtual ~Reader() = default;

        virtual void load_SFML_Sprite(
            const std::shared_ptr<graphics::SFML_Manager>& manager, const std::string& filename
            ) const = 0;
        virtual void load_SFML_Sprite_Group(
            const std::shared_ptr<graphics::SFML_Manager>& manager, const std::string& filename
            ) const = 0;
        [[nodiscard]] virtual std::shared_ptr<graphics::SFML_Manager> load_SFML_Manager(
            const std::shared_ptr<const File_Reader> &fr, const std::string& filename
            ) const = 0;

        [[nodiscard]] virtual std::shared_ptr<logic::collision::HitBoxe> load_HitBoxe(
            const std::string& filename
            ) const = 0;

        [[nodiscard]] virtual std::shared_ptr<graphics::Camera> load_Camera(
            const std::string& filename
            ) const = 0;

        [[nodiscard]] virtual graphics::Tile_Grid_Pair load_Tile_Grid(
            std::shared_ptr<graphics::SFML_Manager> sfml_manager,
            const std::string& filename
            ) const = 0;

        virtual void load_Entities(
            const std::shared_ptr<const File_Reader> &fr,
            const std::shared_ptr<Stage>& stage,
            const std::shared_ptr<logic::Tile_Grid>& grid,
            const std::string& filename
            ) const = 0;

        [[nodiscard]] virtual std::shared_ptr<Stage> load_Stage(
            const std::shared_ptr<const File_Reader>& fr,
            const std::string& filename
            ) const = 0;

        [[nodiscard]] virtual Stage_Manager load_Stage_Manager(
            const std::shared_ptr<const File_Reader>& fr, const std::string& path
            ) const = 0;

        virtual Game_Info get_Game_Info(
            const std::string& filename
            ) = 0;
    };
}

#endif //PACMAN_READER_H