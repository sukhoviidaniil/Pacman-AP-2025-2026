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
#include "infra/io/File_Reader.h"
#include "infra/io/readers/Reader_JSON.h"
#include "infra/event/Event_Bus.h"
#include "core/Game.h"
#include "infra/diagnostics/Logger.h"


int main() {
    infra::diag::Logger::instance();
    const auto eventbus_ = std::make_shared<infra::event::Event_Bus>(); // GLOBAL
    const std::string assets_dir = ASSETS_DIR;
    const std::string conf_dir = assets_dir + "conf/";

    const auto fr = std::make_shared<infra::io::File_Reader>(conf_dir);
    fr->add_Reader(".json", std::make_shared<infra::io::Reader_JSON>());
    infra::ast::Game t = fr->read_Game("conf_game1.json");
    auto a = core::Game(t, conf_dir, eventbus_);
    a.run();
    return 0;
}
