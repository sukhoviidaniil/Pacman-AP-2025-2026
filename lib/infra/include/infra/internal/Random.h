/***************************************************************
 * Project:       Pacman
 * File:          Random.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-25
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
#ifndef PACMAN_RANDOM_H
#define PACMAN_RANDOM_H


#define RAND_INT(min, max) \
infra::Random::instance().next_int((min), (max))

#define RAND_FLOAT(min, max) \
infra::Random::instance().next_float((min), (max))

#define RAND_CHANCE(p) \
infra::Random::instance().chance((p))

#define RAND_ENGINE() \
infra::Random::instance().engine()

#include <random>
#include <cstdint>
namespace infra {

    class Random {
    public:
        using Engine = std::mt19937;

        static Random& instance();

        int next_int(int min, int max);

        float next_float(float min = 0.f, float max = 1.f);

        bool chance(float p);

        Engine& engine();

        Random(const Random&) = delete;
        Random& operator=(const Random&) = delete;

    private:
        Random();

        Engine engine_;
    };
}

#endif //PACMAN_RANDOM_H