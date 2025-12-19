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

#include "LinearLayout.h"

namespace infra::ui {
    class VBox : public LinearLayout {
    protected:
        bool horizontal() const override { return false; }
    };

    class HBox : public LinearLayout {
    protected:
        bool horizontal() const override { return true; }
    };
}

#endif //PACMAN_V_HBOX_H