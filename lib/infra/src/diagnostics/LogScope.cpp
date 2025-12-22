/***************************************************************
 * Project:       Pacman
 * File:          LogScope.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-10
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

#include "infra/diagnostics/LogScope.h"
#include "infra/diagnostics/Logger.h"

namespace infra::diag{
    LogScope::LogScope() {
        Logger::instance().add_depth();
    }

    LogScope::~LogScope() {
        Logger::instance().lower_depth();
    }
}
