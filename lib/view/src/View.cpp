/***************************************************************
 * Project:       Pacman
 * File:          View.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-06
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

#include <utility>

#include "graphics/View.h"

namespace graphics {
    View::View() = default;

    View::View(std::string name) : name_(std::move(name)){
    }

    View::~View() = default;

    std::string View::get_name() const {
        return name_;
    }
}
