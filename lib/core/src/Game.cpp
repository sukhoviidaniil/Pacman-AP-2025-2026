/***************************************************************
 * Project:       Pacman
 * File:          Game.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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

#include "core/Game.h"

#include "core/Stage_Game.h"
#include "graphics/SFML_Manager.h"
#include "graphics/view/Actor_View.h"
#include "logic/model/Actor.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

namespace Core {
    Game::Game() = default;

    void Game::run(const std::string& path) {
        throw;

        Graphics::SFML_Manager ren = Graphics::SFML_Manager();

        //ren.load_texture("sprite.png");

        //ren.load_Sprite_Group("graf_ghosts.json");
        std::shared_ptr<Graphics::Sprite_Group> s = ren.get_Sprite_Group("Blinky");

        Math::Vector2 position = Math::Vector2(0, 0);
        Math::Vector2 direction = Math::Vector2(0, 1);
        float speed = 0.1f;
        std::shared_ptr<Logic::Model::Actor> a = std::make_shared<Logic::Model::Actor>(position, direction, speed);
        std::shared_ptr<Graphics::View::Actor_View> a_v = std::make_shared<Graphics::View::Actor_View>(s);

        a_v->set_actor_model(a);


        std::vector<std::shared_ptr<Logic::Model::Entity>> actors;
        actors.push_back(a);
        std::vector<std::shared_ptr<Graphics::View::Entity_View>> actors_v;
        actors_v.push_back(a_v);


        std::shared_ptr<Logic::Tile_Grid> g = std::make_shared<Logic::Tile_Grid>(3, 3, 10);
        std::shared_ptr<Logic::Collision::World_Collision_Manager> WCM = nullptr;

        std::shared_ptr<Graphics::Camera> camera = std::make_shared<Graphics::Camera>(100, 100);
        camera->set_window_center({200, 200});
        camera->set_logic_center({0,0});


        std::shared_ptr<Stage_Game> stage = std::make_shared<Stage_Game>(actors, g, WCM, actors_v, camera );
        sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

        // Основной цикл программы
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                // Обработка закрытия окна
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Очистка экрана
            window.clear(sf::Color::Black);

            // Отрисовка всего
            // window.draw(...);

            stage->render(window);

            // Вывод содержимого на экран
            window.display();
        }
    }
}
