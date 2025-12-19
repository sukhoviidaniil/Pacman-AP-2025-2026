/***************************************************************
 * Project:       Pacman
 * File:          Logger.h
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
#ifndef PACMAN_LOGGER_H
#define PACMAN_LOGGER_H

#include <fstream>
#include <string>

#ifdef _DEBUG
#define LOG(x) Logger::instance().write(x)
#define LOG_ADD_DEPTH() Logger::instance().add_depth();
#define LOG_LOWER_DEPTH() Logger::instance().lower_depth();
#else
#define LOG(x)
#define LOG_ADD_DEPTH()
#define LOG_LOWER_DEPTH()
#endif

namespace infra::diag {
    class Logger {
    public:
        static Logger& instance();
        void write(const std::string& message);
        void add_depth();
        void lower_depth();
    private:
        Logger();
        std::ofstream logfile_;
        unsigned int depth_;
        std::string indent_str_ = "\t";
        std::string indent(const std::string& message) const;
    };
}


#endif //PACMAN_LOGGER_H