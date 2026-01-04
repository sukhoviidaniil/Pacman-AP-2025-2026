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
#define LOG(x) infra::diag::Logger::instance().write(x)
#define LOG_ADD_DEPTH() infra::diag::Logger::instance().add_depth();
#define LOG_LOWER_DEPTH() infra::diag::Logger::instance().lower_depth();
#else
#define LOG(x)
#define LOG_ADD_DEPTH()
#define LOG_LOWER_DEPTH()
#endif


namespace infra::diag {
    /**
     * @brief Simple singleton logger for debug output.
     *
     * Writes formatted messages to a log file and supports
     * indentation-based depth tracking for structured logs.
     */
    class Logger {
    public:
        /**
         * @brief Returns the global logger instance.
         */
        static Logger& instance();

        /**
         * @brief Writes a message to the log.
         *
         * The message is automatically indented based on
         * the current depth.
         *
         * @param message Text to write.
         */
        void write(const std::string& message);

        /**
         * @brief Increases the indentation depth.
         *
         * Typically used to represent entering a nested scope.
         */
        void add_depth();

        /**
         * @brief Decreases the indentation depth.
         *
         * @note behavior if depth becomes negative -> depth == 0;
         */
        void lower_depth();
    private:
        /**
         * @brief Constructs the logger and opens the log file.
         */
        Logger();
        std::ofstream logfile_; ///< Output log file stream
        unsigned int depth_; ///< Current indentation depth
        std::string indent_str_ = "\t"; ///< String used for one indentation level

        /**
         * @brief Applies indentation to a message.
         *
         * @param message Input message.
         * @return Indented message.
         */
        std::string indent(const std::string& message) const;
    };
}




#endif //PACMAN_LOGGER_H