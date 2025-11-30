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
#include "logic/Logic_Factory.h"
#include "core/Stage.h" // TODO INVALID INCLUDE!!!!


namespace Graphics {
    class Graphics_Factory: public Logic::Logic_Factory{
        public:


        std::shared_ptr<Logic::Tile_Grid> make_grid(std::shared_ptr<Core::Stage> stage, unsigned int width, unsigned int height, float tile_size, const std::vector<std::vector<int>>& grid);

    };
}

#endif //PACMAN_GRAPHICS_FACTORY_H