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


#include "collision/HitBoxe_Shape.h"
#include "logic/Tile_Grid.h"
#include "model/Actor.h"

namespace Logic {
    class Logic_Factory {
        protected:
        [[nodiscard]] static std::shared_ptr<Model::Terrain> make_Terrain(float tile_size, const Math::Vector2& pos, int type);
        [[nodiscard]] static std::shared_ptr<Tile> make_Tile(float tile_size, const Math::Vector2& pos, int type);
        public:
        virtual ~Logic_Factory() = default;

        [[nodiscard]] static std::shared_ptr<Collision::HitBoxe_Shape> make_HitBox(const Collision::HitBoxe_Shape_Info& info);

        [[nodiscard]] static std::shared_ptr<Model::Actor> make_Actor(const Model::Actor_Info& info);

        [[nodiscard]] static std::shared_ptr<Tile_Grid> make_grid(const Tile_Grid_Info &tile_grid_info);
    };
}

#endif //PACMAN_LOGIC_FACTORY_H