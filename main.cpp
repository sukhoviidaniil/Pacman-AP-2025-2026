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
#include "logic/Delta_Timer.h"

int main() {
    const std::string assets_dir = ASSETS_DIR;
    const std::string graphics_dir = assets_dir + "/graphics/";
    const std::string conf_dir = assets_dir + "/config/";
    auto fr = std::make_shared<Core::File_Reader>(graphics_dir, conf_dir);
    fr->add_Reader(".json", std::make_shared<Core::Reader_JSON_public>());
    Core::Info::Game_Info game_info = fr->get_Game_Info("conf_game1.jsom");
    if (game_info.graphics == "SFML") {
        fr->load_SFML_Manager(game_info.graphics_conf);

        unsigned int width = game_info.window_width;
        unsigned int height = game_info.window_height;
        sf::RenderWindow window(sf::VideoMode(width, height), "SFML Window");
        Core::Stage_Manager sm = fr->make_Stage_Manager(game_info.stage_mng);

        Logic::Delta_Timer timer;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            if (window.isOpen()) {
                float delta = timer.tick();
                std::shared_ptr<Core::Stage> stage = sm.get_current_stage();
                stage->simulate(delta);
                stage->render(window);
            }
        }
    }else {
        throw std::runtime_error("Unknown type of graphics");
    }
    return 0;
}
