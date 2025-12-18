/***************************************************************
 * Project:       Pacman
 * File:          Application.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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

#include "core/Application.h"

#include "view/Graphics_Factory.h"
#include "view/View.h"

Application::Application(const infra::ast::Application& a, const std::string& path) {
    models_ = a.models;
    view_ = view::Graphics_Factory::make_View(a.view, path);
}
