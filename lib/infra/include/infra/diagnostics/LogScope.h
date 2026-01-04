/***************************************************************
 * Project:       Pacman
 * File:          LogScope.h
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
#ifndef PACMAN_LOGSCOPE_H
#define PACMAN_LOGSCOPE_H

#ifdef _DEBUG
#define LOG_SCOPE() ::infra::diag::LogScope UNIQUE_NAME(__scope){}
#define UNIQUE_NAME(base) CONCAT(base, __COUNTER__)
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b
#else
#define LOG_SCOPE()
#endif

namespace infra::diag {
    /**
     * @brief RAII helper for automatic log indentation management.
     *
     * Increases the logger indentation level on construction
     * and restores it on destruction.
     *
     * Intended to be used via the LOG_SCOPE() macro.
     */
    class LogScope {
    public:
        /**
         * @brief Constructs the log scope.
         * Increases the logger indentation depth.
         *
         */
        LogScope();

        /**
         * @brief Destroys the log scope and restores previous indentation.
         * Decreases the logger indentation depth.
         */
        ~LogScope();
    };
}

#endif //PACMAN_LOGSCOPE_H