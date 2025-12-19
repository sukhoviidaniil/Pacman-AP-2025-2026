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
#define LOG_SCOPE() LogScope UNIQUE_NAME(__scope){}
#define UNIQUE_NAME(base) CONCAT(base, __COUNTER__)
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b
#else
#define LOG_SCOPE()
#endif

namespace infra::diag {
    class LogScope {
    public:
        LogScope();
        ~LogScope();
    };
}

#endif //PACMAN_LOGSCOPE_H