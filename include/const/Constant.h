/***************************************************************
 * Project:       Pacman
 * File:          Constant.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-10-23
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
#ifndef PACMAN_CONSTANT_H
#define PACMAN_CONSTANT_H
namespace Constants {
    class Constant {
        bool locked = false;
    public:
        Constant();
        ~Constant();
        [[nodiscard]] bool is_locked() const;
    };
}

#endif //PACMAN_CONSTANT_H