/***************************************************************
 * Project:       Pacman
 * File:          TileGrid.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-04
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
#ifndef PACMAN_TILE_GRID_H
#define PACMAN_TILE_GRID_H

#include <optional>

#include "model/grid/TilePos.h"
#include "infra/ast/model/Grid.h"
#include "infra/math/Direction.h"
#include "infra/math/Point2.h"
#include "model/grid/Tile.h"
#include "model/collision/HitBox.h"


namespace model {

    /**
     * @brief Represents a 2D grid of tiles for the game world.
     *
     * Provides utility functions to query positions, centers, and hitboxes.
     */
    class TileGrid {
    public:
        /**
         * @brief Destructor.
         */
        ~TileGrid();

        /**
         * @brief Default constructor.
         */
        explicit TileGrid() = default;

        /**
         * @brief Constructs a TileGrid from a model Grid.
         *
         * @param grid_info Reference to infra::ast::Grid containing layout and tile info
         */
        explicit TileGrid(const infra::ast::Grid &grid_info);

        /// --- Basic grid info ---
        [[nodiscard]] float tile_size() const;
        [[nodiscard]] size_t rows() const;
        [[nodiscard]] size_t columns() const;
        [[nodiscard]] float width() const;
        [[nodiscard]] float height() const;

        /// --- Tile position queries ---
        [[nodiscard]] std::optional<TilePos> get_TilePos(const infra::math::Point2 &pos) const;
        [[nodiscard]] std::optional<TilePos> get_next_TilePos(const infra::math::Point2 &pos, const infra::math::Direction& dir) const;
        [[nodiscard]] infra::math::Point2 get_next_center(const infra::math::Point2& pos, const infra::math::Direction& dir) const;

        /// --- Tile info and hitbox ---
        [[nodiscard]] Tile get_tile(const TilePos& pos) const;
        [[nodiscard]] infra::math::Point2 get_center(const TilePos& pos) const;
        [[nodiscard]] std::unique_ptr<collision::HitBox> get_hitbox(const TilePos& pos) const;

        /// --- Helpers ---
        void out_of_bounds(const TilePos &pos, const std::string &who) const;
        void limit(TilePos& pos) const;

        /**
         * @brief Checks if an entity can choose a new direction from the current tile.
         *
         * @param pos Current tile position
         * @param current_dir Current movement direction
         * @param permission Permission level for traversing tiles
         * @return True if direction can be chosen
         */
        [[nodiscard]] bool can_choose_direction(
            const TilePos &pos,
            infra::math::Direction current_dir,
            Permission permission) const;

    private:
        ///< Dimensions of the grid
        size_t rows_ = 0, columns_ = 0;
        ///< Size of one tile
        float tile_size_ = 0;

        std::vector<
            std::vector<
                Tile
            >
        > tiles_; ///< 2D grid storing tile types
    };
}

#endif //PACMAN_TILE_GRID_H