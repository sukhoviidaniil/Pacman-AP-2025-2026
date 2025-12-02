/***************************************************************
 * Project:       Pacman
 * File:          main.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-10-23
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

#include <string>
#include "core/File_Reader.h"
#include "core/info/Game_Info.h"
#include "core/readers/Reader_JSON.h"
#include "logic/Logic_Factory.h"

int main() {

    const std::string assets_dir = ASSETS_DIR;
    const std::string graphics_dir = assets_dir + "/graphics/";
    const std::string conf_dir = assets_dir + "/config/";
    Core::File_Reader fr(graphics_dir, conf_dir);
    const auto reader_json = std::make_shared<Core::Reader_JSON>();
    fr.add_Reader(".json", reader_json);
    Info::Game_Info game_ingo;

    std::shared_ptr<Logic::Tile_Grid> grid = Logic::Logic_Factory::make_grid(3, 3, 1, {{1, 1, 1}, {1,0,1}, {1,0,1}});
    return 0;
}
