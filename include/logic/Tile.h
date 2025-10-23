/***************************************************************
 * Project:       Pacman
 * File:          Tile.h
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
#ifndef PACMAN_TILE_H
#define PACMAN_TILE_H

class Tile {
    int width = 10, height = 10;
    int pixel_size = 10;
    int status = 0;
    public:
    Tile(int width, int height, int pixel_size, int status);

    void get_consumable(); // TODO: set consumable type
    bool is_walkable() const;
    bool get_center() const;
};

#endif //PACMAN_TILE_H