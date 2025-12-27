/***************************************************************
 * Project:       Pacman
 * File:          Graphics_Factory.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-28
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
#ifndef PACMAN_GRAPHICS_FACTORY_H
#define PACMAN_GRAPHICS_FACTORY_H
#include <memory>

#include "View.h"
#include "infra/ast/Game.h"

namespace view {
    class Graphics_Factory{
        public:

        static std::shared_ptr<View> make_View(const infra::ast::View &info, const std::string &path);

    private:

        static void Register(
            std::unordered_map<
                std::string,
                std::shared_ptr<View> (*)(const infra::ast::View&, const std::string&)
            > &outMap
        );

        static std::shared_ptr<View> SFML_View(const infra::ast::View& info, const std::string& path);
    };
}

#endif //PACMAN_GRAPHICS_FACTORY_H