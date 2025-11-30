/***************************************************************
 * Project:       Pacman
 * File:          Warning.h
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
#ifndef PACMAN_WARNING_H
#define PACMAN_WARNING_H

#include <string>

namespace Info {
    class Warning {

        std::string what_;
        public:
        explicit Warning(const std::string& what);
        virtual ~Warning();

        [[nodiscard]] const std::string& what() const;
    };
}

#endif //PACMAN_WARNING_H