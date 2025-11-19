/***************************************************************
 * Project:       Pacman
 * File:          open_file.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-08
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
#ifndef PACMAN_OPEN_FILE_H
#define PACMAN_OPEN_FILE_H
#include <fstream>
#include <iostream>
#include <stdexcept>

inline std::ifstream open_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file " + filename + "!\n";
        throw std::runtime_error("File not opened");
    }
    return file;
}

#endif //PACMAN_OPEN_FILE_H