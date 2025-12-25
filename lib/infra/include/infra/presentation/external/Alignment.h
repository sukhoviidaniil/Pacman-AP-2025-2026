/***************************************************************
 * Project:       Pacman
 * File:          Alignment.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-19
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
#ifndef PACMAN_ALIGNMENT_H
#define PACMAN_ALIGNMENT_H

namespace infra::ui {

    /**
     * @brief Alignment policy used by the layout engine.
     *
     * Defines how an element is positioned or sized along an axis
     * relative to the available layout space.
     */
    enum class Align {
        Start,  ///< Align to the beginning of the available space
        Center, ///< Center within the available space
        End,    ///< Align to the end of the available space
        Stretch ///< Stretch to fill the available space
    };
}

#endif //PACMAN_ALIGNMENT_H