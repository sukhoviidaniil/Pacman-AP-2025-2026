/***************************************************************
 * Project:       Pacman
 * File:          Logic_Factory.h
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
#ifndef PACMAN_LOGIC_FACTORY_H
#define PACMAN_LOGIC_FACTORY_H


#include "logic/Tile_Grid.h"

namespace Logic {
    class Logic_Factory {
        protected:
        static std::shared_ptr<Model::Terrain> make_Terrain(float tile_size, const Math::Vector2& pos, int type);
        static std::shared_ptr<Tile> make_Tile(float tile_size, const Math::Vector2& pos, int type);
        public:
        virtual ~Logic_Factory() = default;

        [[nodiscard]] virtual std::shared_ptr<Tile_Grid> make_grid(unsigned int width, unsigned int height, float tile_size, const std::vector<std::vector<int>>& grid) const;
    };
}

#endif //PACMAN_LOGIC_FACTORY_H