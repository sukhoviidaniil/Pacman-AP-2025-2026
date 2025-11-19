/***************************************************************
 * Project:       Pacman
 * File:          HitBoxe.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-16
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

#include "logic/collision/HitBoxe.h"

namespace Logic::Collision {
    HitBoxe::HitBoxe(const unsigned int layer, const unsigned int strength):
    layer_(layer), strength_(strength){
    }

    unsigned int HitBoxe::get_layer() const {
        return layer_;
    }

    unsigned int HitBoxe::get_strength() const {
        return strength_;
    }

    std::vector<Math::Vector2> HitBoxe::get_vector_to(const HitBoxe &hit_boxe) const {
        const std::vector<Math::Vector2> m_centers = get_centers();
        const std::vector<Math::Vector2> f_centers = hit_boxe.get_centers();
        std::vector<Math::Vector2> all_centers;
        for (const auto& f_center : f_centers) {
            for (const auto& m_center : m_centers) {
                Math::Vector2 dir = f_center - m_center;
                all_centers.push_back(dir);
            }
        }
        return all_centers;
    }
}
