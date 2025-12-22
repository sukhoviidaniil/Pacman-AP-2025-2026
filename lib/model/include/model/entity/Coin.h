/***************************************************************
 * Project:       Pacman
 * File:          Coin.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-16
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
#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H
#include "Entity.h"

namespace model::entity {
    class Coin : public Entity{
    public:
        ~Coin() override;
    };
}

#endif //PACMAN_COIN_H