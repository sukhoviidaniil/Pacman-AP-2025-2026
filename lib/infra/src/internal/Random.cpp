/***************************************************************
 * Project:       Pacman
 * File:          Random.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2026-01-01
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

#include "infra/internal/Random.h"

namespace infra {
    Random & Random::instance()  {
        static Random inst;
        return inst;
    }

    int Random::next_int(int min, int max)  {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine_);
    }

    float Random::next_float(float min, float max)  {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(engine_);
    }

    bool Random::chance(float p)  {
        std::bernoulli_distribution dist(p);
        return dist(engine_);
    }

    Random::Engine & Random::engine() {
        return engine_;
    }

    Random::Random() : engine_(
        std::random_device{}()
        ) {

    }
}
