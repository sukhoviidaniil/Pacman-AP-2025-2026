/***************************************************************
 * Project:       Pacman
 * File:          ScoreView.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-25
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
#ifndef PACMAN_SCOREVIEW_H
#define PACMAN_SCOREVIEW_H
#include "infra/Score.h"

namespace infra {
    class ScoreView {
    public:
        explicit ScoreView(const infra::Score& s) : score_(s) {}

    private:
        const Score& score_;
    };
}

#endif //PACMAN_SCOREVIEW_H