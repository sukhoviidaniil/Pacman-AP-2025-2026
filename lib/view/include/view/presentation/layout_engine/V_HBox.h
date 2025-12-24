/***************************************************************
 * Project:       Pacman
 * File:          V_HBox.h
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
#ifndef PACMAN_V_HBOX_H
#define PACMAN_V_HBOX_H

#include "view/presentation/layout_engine/LinearLayout.h"

namespace view::ui {
    /**
     * @brief Vertical box layout.
     *
     * Arranges child elements vertically in a single column.
     * Inherits linear layout behavior with horizontal() = false.
     */
    class VBox : public LinearLayout {
    protected:
        /// @brief Indicates that the layout is vertical.
        bool horizontal() const override { return false; }
    };

    /**
     * @brief Horizontal box layout.
     *
     * Arranges child elements horizontally in a single row.
     * Inherits linear layout behavior with horizontal() = true.
     */
    class HBox : public LinearLayout {
    protected:
        /// @brief Indicates that the layout is horizontal.
        bool horizontal() const override { return true; }
    };
}

#endif //PACMAN_V_HBOX_H