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

#include "../lib/infra/include/infra/io/File_Reader.h"
#include "infra/readers/Reader_JSON.h"
/*
#include "core/File_Reader.h"
#include "core/info/Game_Info.h"
#include "core/readers/Reader_JSON.h"
#include "lib/gen/include/gen/Logger.h"
#include "lib/gen/include/gen/LogScope.h"
#include "lib/model/include/model/Delta_Timer.h"
*/


int main() {
    const std::string assets_dir = ASSETS_DIR;
    const std::string conf_dir = assets_dir + "/conf/";

    auto fr = std::make_shared<infra::File_Reader>(conf_dir);
    fr->add_Reader(".json", std::make_shared<infra::Reader_JSON>());
    infra::ast::Application t = fr->read_Application("conf_game1.json");
    /*

    const std::string assets_dir = ASSETS_DIR;
    const std::string graphics_dir = assets_dir + "/graphics/";
    const std::string conf_dir = assets_dir + "/conf/";
    auto fr = std::make_shared<core::File_Reader>(graphics_dir, conf_dir);
    fr->add_Reader(".json", std::make_shared<core::Reader_JSON>());
    core::Game_Info game_info = fr->get_Game_Info("conf_game1.json");
    if (game_info.graphics == "SFML") {
        fr->load_SFML_Manager(game_info.graphics_conf);

        auto scene_width = static_cast<float>(game_info.window_width);
        auto scene_height = static_cast<float>(game_info.window_height);
        sf::RenderWindow window(sf::VideoMode(scene_width, scene_height), "SFML Window");
        sf::View view(sf::FloatRect(0, 0, scene_width, scene_height));
        window.setView(view);
        window.setFramerateLimit(30);
        core::Stage_Manager sm = fr->load_Stage_Manager(game_info.stage_mng);

        logic::Delta_Timer timer;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Resized) {
                    float aspect_ratio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
                    float view_width = scene_width;
                    float view_height = scene_height;
                    if (aspect_ratio > scene_width / scene_height) {
                        view_width = scene_height * aspect_ratio;
                    } else {
                        view_height = scene_width / aspect_ratio;
                    }
                    view.setSize(view_width, view_height);
                    window.setView(view);
                }
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
                //stage->action(event);
            }

            window.clear();

            float delta = timer.tick();
            std::shared_ptr<core::Stage> stage = sm.get_current_stage();
            stage->simulate(delta);
            stage->render(window);
            window.display();
        }
    }else {
        throw std::runtime_error("Unknown type of graphics");
    }
    */
    return 0;
}
