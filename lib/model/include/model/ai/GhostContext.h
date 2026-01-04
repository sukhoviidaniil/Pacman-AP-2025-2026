/***************************************************************
 * Project:       Pacman
 * File:          GhostContext.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-28
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
#ifndef PACMAN_GHOSTCONTEXT_H
#define PACMAN_GHOSTCONTEXT_H
#include <span>

#include "internal/GhostMode_State.h"
#include "infra/math/Direction.h"

#include "model/grid/TileGrid.h"

namespace model::ai {

    /**
     * @brief Shared context available to all ghost AI instances.
     *
     * Contains global game state information that may influence
     * decision-making of multiple ghosts.
     */
    struct GlobalGhostContext {
        /**
         * @brief Reference to the tile-based game map.
         */
        const TileGrid& map;

        /**
         * @brief Current tile position of Pac-Man.
         */
        TilePos pacman_pos;

        /**
         * @brief Remaining duration of a global buff or power-up.
         *
         * @note Purpose and exact semantics depend on game rules.
         */
        float buff_duration;

        /**
         * @brief Current movement direction of Pac-Man.
         */
        infra::math::Direction pacman_direction;

        /**
         * @brief Positions of Blinky ghosts.
         *
         * Provided as a read-only view over tile positions.
         *
         * @todo Clarify why only Blinky positions are exposed
         *       and how they are used by other ghosts.
         */
        std::span<const TilePos> blinky_positions;
    };

    /**
     * @brief Context specific to a single ghost instance.
     *
     * Contains per-ghost state used by AI logic and behavior selection.
     */
    struct UniqGhostContext {
        /**
         * @brief Current permission or restriction state.
         *
         */
        Permission permission;

        /**
         * @brief Current ghost behavior mode.
         */
        GhostMode mode;

        /**
         * @brief Current tile position of the ghost.
         */
        TilePos self_pos;

        /**
         * @brief Current movement direction of the ghost.
         */
        infra::math::Direction self_direction;

        /**
         * @brief Index of this ghost among all ghost instances.
         *
         * @note Used to distinguish ghosts or access peer-related data.
         */
        std::size_t self_index; // index among peers
    };
}

#endif //PACMAN_GHOSTCONTEXT_H