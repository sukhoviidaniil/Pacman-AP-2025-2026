/***************************************************************
 * Project:       Pacman
 * File:          Error.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-29
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
#ifndef PACMAN_ERROR_H
#define PACMAN_ERROR_H


#include "Warning.h"

namespace Core::Info {
    class Error final : public Warning {
        public:
        explicit Error(const std::string& what);
        ~Error() override;
    };
}

#endif //PACMAN_ERROR_H