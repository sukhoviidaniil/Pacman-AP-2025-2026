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

#include "Application.h"

#include "view/View.h"

Application::Application(infra::ast::Application a) {

    view_ = view::View(a.view);




}
