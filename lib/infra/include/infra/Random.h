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

#include <random>
#include <cstdint>
namespace infra {

    class Random {
    public:
        using Engine = std::mt19937;

        static Random& instance() {
            static Random inst;
            return inst;
        }

        int next_int(int min, int max) {
            std::uniform_int_distribution<int> dist(min, max);
            return dist(engine_);
        }

        float next_float(float min = 0.f, float max = 1.f) {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(engine_);
        }

        bool chance(float p) {
            std::bernoulli_distribution dist(p);
            return dist(engine_);
        }

        Engine& engine() { return engine_; }

        Random(const Random&) = delete;
        Random& operator=(const Random&) = delete;

    private:
        Random()
            : engine_(std::random_device{}()) {}

        Engine engine_;
    };
}

#endif //PACMAN_RANDOM_H