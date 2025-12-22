/***************************************************************
 * Project:       Pacman
 * File:          LayoutResult.h
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
#ifndef PACMAN_LAYOUTRESULT_H
#define PACMAN_LAYOUTRESULT_H

#include "infra/presentation/base/Rect.h"

namespace infra::ui {
    /**
     * @brief Result of a layout computation.
     *
     * Contains the resolved rectangle assigned to a UI element
     * after the layout engine finishes its calculations.
     */
    struct LayoutResult {
        Rect rect; ///< Final computed rectangle
    };
}


#endif //PACMAN_LAYOUTRESULT_H