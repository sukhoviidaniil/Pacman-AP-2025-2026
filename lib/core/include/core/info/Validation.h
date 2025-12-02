/***************************************************************
 * Project:       Pacman
 * File:          Validation.h
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
#ifndef PACMAN_VALIDATION_H
#define PACMAN_VALIDATION_H
#include <vector>

#include "Error.h"

namespace Core::Info {
    class Validation {
        bool valid_ = true;
        std::vector<Error> errors_;
        std::vector<Warning> warnings_;
        public:

        Validation();
        ~Validation();
        [[nodiscard]] bool valid() const;
        [[nodiscard]] const std::vector<Error>& errors() const;
        [[nodiscard]] const std::vector<Warning>& warnings() const;
        void add(const Error& error);
        void add(const Warning& warning);
    };
}

#endif //PACMAN_VALIDATION_H