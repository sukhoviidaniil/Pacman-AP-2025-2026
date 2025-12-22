/***************************************************************
 * Project:       Pacman
 * File:          Score.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-21
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

#include "infra/Score.h"
namespace infra {
    Score::Score() = default;

    Score::~Score() = default;

    void Score::track_local(const std::shared_ptr<infra::event::Event_Bus> &bus) {

    }
}
